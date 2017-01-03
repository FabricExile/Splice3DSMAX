#include "StdAfx.h"
#include "DockableWidget.h"
#include <qwidget.h>
#include "QApplication"
#include <QMfcApp>

//////////////////////////////////////////////////////////////////////////

DockableWindow::DockableWindow(HWND hWnd, FabricTranslationFPInterface* owner) 
 : m_hWnd(hWnd)
 , m_contentWidget(NULL)
 , m_cuiFrame(NULL)
 , m_owner(owner)
{
	m_cuiFrame = ::GetICUIFrame( m_hWnd );
	m_cuiFrame->SetContentType(CUI_HWND);
	m_cuiFrame->InstallMsgHandler(this);

	// Ensure our QtApp is initialized
	AcquireQt();
}

DockableWindow::~DockableWindow()
{
	WriteSettings();

	::ReleaseICUIFrame(m_cuiFrame);

	delete m_contentWidget;

	DestroyWindow(m_hWnd);

	// #FABMAX-50 - Only release Qt on plugin release,
	// Doing so frequently will cause Qt to re-initialize itself
	// and write over changes FabricUI has made
	//ReleaseQt();
}


void DockableWindow::ResizeFrameToContent()
{
	RECT r = { 0 };
	if (m_contentWidget == NULL) return;
	GetWindowRect(m_hWnd, &r);
	MoveWindow(m_hWnd, r.left, r.top, m_contentWidget->width(), m_contentWidget->height(), FALSE);
}

void DockableWindow::ResizeContentToFrame()
{
	RECT r = { 0 };
	GetWindowRect( m_hWnd, &r );
	ResizeContentToFrame( &r );
}

void DockableWindow::ResizeContentToFrame(RECT* pNewSize)
{
	if (m_contentWidget == NULL)
		return;

	int width = pNewSize->right - pNewSize->left;
	int height = pNewSize->bottom - pNewSize->top;
	m_contentWidget->resize(width, height);

	// Our QWinWidget does not appear to be handling resizing its children - lets
	// manually pass-through the resize until we have a more elegant method
	QObjectList contentChildren = m_contentWidget->children();
	DbgAssert(contentChildren.size() == 1);
	if (contentChildren.size() > 0)
	{
		QWidget* pChildWidget = dynamic_cast<QWidget*>(contentChildren[0]);
		if (pChildWidget != nullptr)
		{
			// Magic subtraction values come from not-sure-where?
			// Possibly trial-and-error
			pChildWidget->resize(width - 16, height - 40);
		}
	}
}

int DockableWindow::GetWidth(int sizeType, int orient)
{
	switch (sizeType) {
	case CUI_MIN_SIZE: return 50;
	case CUI_MAX_SIZE: return 10000;
	}
	return m_contentWidget->width();
}

int DockableWindow::GetHeight(int sizeType, int orient)
{
	switch (sizeType) {
	case CUI_MIN_SIZE: return 50;
	case CUI_MAX_SIZE: return 10000;
	}
	return m_contentWidget->height();
}

DockableWindow* DockableWindow::Create(const MCHAR* name, FabricTranslationFPInterface* owner, DockFlags pos /*= None*/, DWORD initialPos /*= 0*/, bool isDockedInitially /*= false*/, bool resizable /*= true*/, bool visible /*= true*/)
{
	HWND h = ::CreateCUIFrameWindow(
		::GetCOREInterface()->GetMAXHWnd(), name, 0, 0, 0, 0);
	if (!h) 
		return NULL;

	DockableWindow* r = new DockableWindow(h, owner);
	ICUIFrame* f = r->GetICUIFrame();

	DWORD flags = pos | CUI_FLOATABLE | CUI_DONT_SAVE;
	if (resizable) 
		flags |= CUI_SM_HANDLES;
	f->SetPosType(flags);
	if (isDockedInitially) 
		r->Dock(initialPos);

	f->Hide(visible ? FALSE : TRUE);
	return r;
}

int DockableWindow::ProcessMessage( UINT message, WPARAM wParam, LPARAM lParam )
{
	switch (message) {
	case WM_ACTIVATE:
		// If our window is deactivated, let max have it's kb accelerators back.
		// We cannot use WM_KILLFOCUS unfortunately, because the dialog sends
		// this message internally when switching internal windows.
		if (LOWORD(wParam) == WA_INACTIVE)
			EnableAccelerators(); // DFG win Deactivated, max can accelerate
		break;
	case WM_CLOSE:
		m_owner->CloseDFGGraphEditor();
		break;
	case WM_SETFOCUS:
		// When we gain focus, start owning that keyboard input!
		DisableAccelerators();
		break;
	case CUI_POSDATA_MSG: {
		CUIPosData **cpd = (CUIPosData **)lParam;
		cpd[0] = this;
		return TRUE;
	}
	case WM_SHOWWINDOW:
		// On creation, we do not receive a message WM_ACTIVATE, so
		// we assume (yes, risky) that we have focus and will be accepting keys
		DisableAccelerators();
		break;
	case WM_SIZE:
	{
		ResizeContentToFrame();
		return FALSE;
	}
	case WM_KEYDOWN:
	case WM_KEYUP:
		return TRUE;
	}
	return FALSE;
}

bool DockableWindow::HasWidget()
{
	return GetWidget() != NULL;
}

QWidget* DockableWindow::GetWidget()
{
	return m_contentWidget;
}

void DockableWindow::SetWidget(QWidget* widget)
{
	delete(this->m_contentWidget);
	this->m_contentWidget = widget;
	if (widget == NULL) return;
	widget->move(0, 0);
	ResizeFrameToContent();
	// Just to verify - reframe our content as well
	ResizeContentToFrame();

	widget->show();
}

void DockableWindow::Dock(DWORD location)
{
	if (location & Top) GetCUIFrameMgr()->DockCUIWindow(m_hWnd, Top);
	else if (location & Bottom) GetCUIFrameMgr()->DockCUIWindow(m_hWnd, Bottom);
	else if (location & Left) GetCUIFrameMgr()->DockCUIWindow(m_hWnd, Left);
	else if (location & Right) GetCUIFrameMgr()->DockCUIWindow(m_hWnd, Right);
}

void DockableWindow::Float()
{
	GetCUIFrameMgr()->FloatCUIWindow(m_hWnd);
}

HWND DockableWindow::GetHWND()
{
	return m_hWnd;
}

ICUIFrame* DockableWindow::GetICUIFrame()
{
	return m_cuiFrame;
}

MSTR GetCfgFile()
{
	const MSTR& fabricMaxDir = GetFabricMaxEnvDir();
	return fabricMaxDir + _M( "windowPos.ini" );
}

void DockableWindow::ReadSettings()
{
	MSTR cfgFile = GetCfgFile();
	QSettings settings( ToQStr( cfgFile ), QSettings::IniFormat );

	RECT rect;
	GetWindowRect( m_hWnd, &rect );

	const MCHAR* name = m_cuiFrame->GetName();
	settings.beginGroup( ToQStr( name ) );
	rect.top = settings.value( "top", rect.top ).toUInt();
	rect.right = settings.value( "right", rect.right ).toUInt();
	rect.left = settings.value( "left", rect.left ).toUInt();
	rect.bottom = settings.value( "bottom", rect.bottom ).toUInt();

	MoveWindow( m_hWnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, false );

	ResizeContentToFrame();
}

void DockableWindow::WriteSettings()
{
	RECT rect;
	GetWindowRect( m_hWnd, &rect );

	MSTR cfgFile = GetCfgFile( );
	QSettings settings( ToQStr(cfgFile), QSettings::IniFormat );

	const MCHAR* name = m_cuiFrame->GetName();
	settings.beginGroup( ToQStr(name) );
	settings.setValue( "top", rect.top );
	settings.setValue( "right", rect.right );
	settings.setValue( "left", rect.left );
	settings.setValue( "bottom", rect.bottom );
	settings.endGroup();
}

//////////////////////////////////////////////////////////////////////////

static int s_qt_count = 0;
static bool s_own_qt = false;
void AcquireQt()
{
	if (s_qt_count == 0)
	{
		s_qt_count++;
		s_own_qt = QMfcApp::pluginInstance( hInstance );
	}
}

void ReleaseQt()
{
	if (s_qt_count != 0 && s_own_qt)
	{
		delete qApp;
	}
}