#pragma once

#ifndef DEBUG

#define MAXSPLICE_CATCH_BEGIN() \
	try {

#define MAXSPLICE_CATCH_END \
    } \
	catch (FabricCore::Exception e) { \
		logMessage(e.getDesc_cstr()); \
    } \
	catch (...) \
	{ \
		logMessage("ERROR: Unhandled exception."); \
	}

#define MAXSPLICE_CATCH_RETURN(value) \
	    } \
	catch (FabricCore::Exception e) { \
		logMessage(e.getDesc_cstr()); \
		return value; \
	} \
	catch (...) \
	{ \
		logMessage("ERROR: Unhandled exception."); \
		return value; \
	}

#else
// In debug mode, we do not want exceptions to be caught.  Ever...
#define MAXSPLICE_CATCH_BEGIN()
#define MAXSPLICE_CATCH_END
#define MAXSPLICE_CATCH_RETURN(value)
#endif


