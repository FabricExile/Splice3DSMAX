/**********************************************************************
*<
FILE: DllEntry.cpp

DESCRIPTION:	Returns the ClassDesc (factory pattern) classes 
				to allow Max to create our plugins

CREATED BY:		Stephen Taylor, T&A Development

*>
**********************************************************************/

#include "StdAfx.h"
#include "FabricStaticFPInterface.h"
#include <notify.h>
#include <MaxScript/MaxScript.h>
#include "FabricEvents.h"
#include "DockableWidget.h"

// This function is called by Windows when the DLL is loaded.  This 
// function may also be called many times during time critical operations
// like rendering.  Therefore developers need to be careful what they
// do inside this function.  In the code below, note how after the DLL is
// loaded the first time only a few statements are executed.
BOOL WINAPI DllMain(HINSTANCE hinstDLL,ULONG fdwReason,LPVOID /*lpvReserved*/)
{
	if( fdwReason == DLL_PROCESS_ATTACH )
	{
		hInstance = hinstDLL;
		// Hang on to this DLL's instance handle.
		DisableThreadLibraryCalls(hinstDLL);
	}
	return(TRUE);
}


extern ClassDesc2* GetDynPBlockClassDesc();;
extern DynPBCustAttrClassDesc* GetFabricControllerDesc();

#ifdef __cplusplus
extern "C" {  // only need to export C interface if
	// used by C++ source code
#endif

// This function returns a string that describes the DLL and where the user
// could purchase the DLL if they don't have it.
__declspec( dllexport ) const TCHAR* LibDescription()
{
	return GetString(IDS_LIBDESCRIPTION);
}

// This function returns the number of plug-in classes this DLL
__declspec( dllexport ) int LibNumberClasses()
{
	return 11;
}

// This function returns the number of plug-in classes this DLL

__declspec( dllexport ) ClassDesc* LibClassDesc(int i)
{
	switch(i) {
	case 0: return FabricTranslationLayer<Control, float>::GetClassDesc();
	case 1: return FabricTranslationLayer<Control, Point3>::GetClassDesc();
	case 2: return FabricTranslationLayer<Control, Quat>::GetClassDesc();
	case 3: return FabricTranslationLayer<Control, Matrix3>::GetClassDesc();
	case 7: return FabricTranslationLayer<OSModifier, Mesh>::GetClassDesc();
	case 8: return FabricTranslationLayer<WSModifier, Mesh>::GetClassDesc();
	case 9: return FabricTranslationLayer<GeomObject, Mesh>::GetClassDesc();
	case 10: return FabricTranslationLayer<ReferenceTarget, int>::GetClassDesc();
	default: return nullptr;
	}
}

// This function returns a pre-defined constant indicating the version of 
// the system under which it was compiled.  It is used to allow the system
// to catch obsolete DLLs.
__declspec( dllexport ) ULONG LibVersion()
{
	return VERSION_3DSMAX;
}

// By returning FALSE from CanAutoDefer, we opt
// out of 3ds Max's deferred loading. 
__declspec( dllexport ) ULONG CanAutoDefer()
{
	return FALSE;
}

// Initialize things
void OnStartup(void* /*param*/, NotifyInfo* /*info*/)
{
	// setup the callback functions
	InitLoggingTimer();

	// Magic initialization stuff for maxscript.
	static bool menus_setup = false;
	if (!menus_setup) {
		init_MAXScript();
		menus_setup = TRUE;

		// On first run, evaluate the script that defines our function
		const MSTR& mxsMenuSetup = GetFabricMaxEnvDir( );
		bool success = false;
		if (!mxsMenuSetup.isNull()) {
			MSTR mxsMenuSetupPath = mxsMenuSetup + _T("SetupMenu.ms");
			success = filein_script_ex(mxsMenuSetupPath.data(), _M("** Error loading Fabric menu: env variable FABRIC3DSMAXDIR not set **") );
		}
		
		if (!success)
		{
			logMessage( "** Error loading Fabric menu: env variable FABRIC3DSMAXDIR not set **" );
		}
	}

	// Cleanup once callback is done.
	UnRegisterNotification(OnStartup, nullptr);
}

// Clean up splice, and unhook all notifications.
void OnShutdown(void* param, NotifyInfo* info)
{
	// On shutdown we release all info
	FabricStaticFPInterface::GetInstance()->DestroyClient(true);
	UnRegisterNotification(OnShutdown, nullptr);
	// Cleanup once callback is done.

	ReleaseQt();
	Free3dsMaxEnvDir();
}

__declspec( dllexport ) int LibInitialize(void)
{
	// We need to initialize our MaxScript exposure for all classes as well.
	FabricTranslationLayer<Control, float>::InitMixinInterface();
	FabricTranslationLayer<Control, Point3>::InitMixinInterface();
	FabricTranslationLayer<Control, Quat>::InitMixinInterface();
	FabricTranslationLayer<Control, Matrix3>::InitMixinInterface();
	FabricTranslationLayer<OSModifier, Mesh>::InitMixinInterface();
	FabricTranslationLayer<WSModifier, Mesh>::InitMixinInterface();
	FabricTranslationLayer<GeomObject, Mesh>::InitMixinInterface();
	FabricTranslationLayer<ReferenceTarget, int>::InitMixinInterface();

	FabricStaticFPInterface::GetInstance();

	// Force init/cleanup of client
	RegisterNotification(OnStartup, NULL, NOTIFY_SYSTEM_STARTUP);
	RegisterNotification(OnShutdown, NULL, NOTIFY_SYSTEM_SHUTDOWN);
	return TRUE;
}

// This function is called once, just before the plugin is unloaded. 
// Perform one-time plugin un-initialization in this method."
// The system doesn't pay attention to a return value.
__declspec( dllexport ) int LibShutdown(void)
{
	// Disable logging, the MaxScript system has already exit
	//Fabric::Logging::setLogFunc(nullptr);
	//Fabric::Logging::setLogErrorFunc(nullptr);
	//Fabric::Logging::setCompilerErrorFunc(nullptr);
	//Fabric::Logging::setKLReportFunc(nullptr);
	//Fabric::Logging::setKLStatusFunc(nullptr);

	//Fabric::Finalize();
	return TRUE;
}

#ifdef __cplusplus
}
#endif
