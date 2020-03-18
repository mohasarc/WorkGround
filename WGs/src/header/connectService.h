#ifndef APP_H
#define APP_H
#include <tchar.h>
#include <Windows.h>
#include "workGround.h"
#include <tlhelp32.h>

// Functions
extern bool storeToMem(HANDLE hPipe, WorkGround activeWG);
extern bool retrieveFromMem(HANDLE hPipe, int wgID, WorkGround& WGtoTerminate);
extern bool startService();
extern bool connect(HANDLE& hPipe);
extern bool sendOpCode(HANDLE hPipe, int opCode);
extern bool IsProcessRunning(const TCHAR* const executableName);

// constantss
const int DELETE_WG = 0;
const int RETRIEVE_WG = 1;
const int STORE_WG = 2;
const int SEND_ID = 3;
#endif