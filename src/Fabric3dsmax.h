#pragma once

#include <FabricUI/Application/FabricException.h>

#ifdef DEBUG
#define DBGONLYMSG(text, caption) MaxMsgBox(NULL, text, caption, MB_OK)
#else
#define DBGONLYMSG(text, caption) 
#endif

#ifndef _DEBUG

#define MAXSPLICE_CATCH_BEGIN \
	try {

#define MAXSPLICE_CATCH_END \
	} \
	catch (FabricCore::Exception e) { \
		logMessage(e.getDesc_cstr()); \
		DBGONLYMSG(MSTR::FromACP(e.getDesc_cstr()), _M("FabricException")); \
	} 

#define MAXSPLICE_CATCH_RETURN(value) \
		} \
	catch (FabricCore::Exception e) { \
		logMessage(e.getDesc_cstr()); \
		return value; \
	} \
  catch (FabricUI::Application::FabricException &e) \
  { \
  	logMessage(e.what()); \
    return value; \
  } 

// When catching from an FPInterface function, the best thing to do
// is re-throw with Fabric's error code.
#define MAXSCRIPT_CATCH_END \
	} \
	catch (FabricCore::Exception e) { \
		logMessage(e.getDesc_cstr()); \
		throw UserThrownError(MSTR::FromACP(e.getDesc_cstr()), FALSE); \
	}  \
  catch (FabricUI::Application::FabricException &e) \
  { \
  	logMessage(e.what()); \
    FabricUI::Application::FabricException::Throw( \
      "Caught App Exception", \
      e.what() \
      ); \
  } 

#else
// In debug mode, we do not want exceptions to be caught.  Ever...
#define MAXSPLICE_CATCH_BEGIN
#define MAXSPLICE_CATCH_END
#define MAXSPLICE_CATCH_RETURN(value)
#define MAXSCRIPT_CATCH_END
#endif


