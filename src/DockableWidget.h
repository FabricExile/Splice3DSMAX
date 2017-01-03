//
// DockableWindow allows hosting QT content in a Win32 frame
// that can be docked within the Max docking system
//

class QWidget;

class DockableWindow
	: public CUIPosData, public CUIFrameMsgHandler
{
	MSTR m_name;
	HWND m_hWnd;
	ICUIFrame* m_cuiFrame;
	QWidget* m_contentWidget;
	FabricTranslationFPInterface* m_owner;

	DockableWindow(HWND hWnd, FabricTranslationFPInterface* owner);

	void ResizeFrameToContent();

	void ResizeContentToFrame();
	void ResizeContentToFrame( RECT* pNewSize );

	int GetWidth( int sizeType, int orient ) override;

	int GetHeight(int sizeType, int orient) override;

public:

	enum DockFlags {
		None = 0,
		Top = 1 << 0,
		Bottom = 1 << 1,
		Left = 1 << 2,
		Right = 1 << 3,
		Horizontal = Left | Right,
		Vertical = Top | Bottom,
		All = Horizontal | Vertical,
	};

	virtual ~DockableWindow();

	static DockableWindow* Create(const MCHAR* name, 
								   FabricTranslationFPInterface* owner, 
								   DockFlags pos = None,
								   DWORD initialPos = 0,
								   bool isDockedInitially = false, 
								   bool resizable = true,
								   bool visible = true);

	virtual int ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

	bool HasWidget();

	QWidget* GetWidget();

	void SetWidget(QWidget* w);

	void Dock(DWORD location);

	void Float();

	HWND GetHWND();

	ICUIFrame* GetICUIFrame();
	
	// The owning class persists the dlg position
	void SetDlgPosition( RECT& position );
	RECT GetDlgPosition();
};

extern void AcquireQt();
extern void ReleaseQt();