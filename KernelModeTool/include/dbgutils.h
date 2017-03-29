#pragma once


/**
  * Either compile for debug or not.
  */
#define _DEBUG


/**
  * If compiling for debug, then define debugging utilities.
  * Otherwise, define the debugging utilities' names as nothing.
  */
#ifdef _DEBUG

#define DEBUG_PRINT(...) DbgPrint(__VA_ARGS__)

#else

#define DEBUG_PRINT(...) ;

#endif // _DEBUG
