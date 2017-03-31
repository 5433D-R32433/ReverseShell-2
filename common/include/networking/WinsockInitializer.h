#pragma once


namespace networking
{
/**
  * Function initiates use of the Winsock 2 DLL by the process.
  * Call this once for the program.
  * @return error code -
  *     https://msdn.microsoft.com/en-us/library/windows/desktop/ms742213(v=vs.85).aspx
  */
int WinsockInit();

/**
  * Function cleans use of the Winsock 2 DLL by the process.
  * Call this once for the program after calling WinsockInit.
  * @return error code -
  *     https://msdn.microsoft.com/en-us/library/windows/desktop/ms741549(v=vs.85).aspx
  */
int WinsockCleanup();
}
