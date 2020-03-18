#ifndef APP_H
#define APP_H
#include <tlhelp32.h>
#include <tchar.h>
#include <Windows.h>
#include "workGround.h"

// Functions
bool static storeToMem(HANDLE hPipe, WorkGround activeWG);
bool static retrieveFromMem(HANDLE hPipe, int wgID, WorkGround& WGtoTerminate);
bool static startService();
bool static connect(HANDLE& hPipe);
bool static IsProcessRunning(const TCHAR* const executableName);

// constantss
const int DELETE_WG = 0;
const int RETRIEVE_WG = 1;
const int STORE_WG = 2;
const int SEND_ID = 3;
#endif