#ifndef CONNECTSERVICE_H
#define CONNECTSERVICE_H
#include <tchar.h>
#include <Windows.h>
#include "workground.h"
#include <tlhelp32.h>
#include <sstream>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>
#include <vector>
#include <string>
#include <map>
#define BUFSIZE 4096
using namespace std;

// Functions
extern bool storeToMem(HANDLE hPipe, WorkGround activeWG);
extern bool retrieveFromMem(HANDLE hPipe, int wgID, WorkGround& WGtoTerminate);
extern bool startService();
extern bool connect(HANDLE& hPipe);
extern bool sendRequest(HANDLE hPipe, int opCode);
extern bool IsProcessRunning(const TCHAR* const executableName);
extern bool terminateService(HANDLE hPipe);
extern bool capture(std::vector<string> &paths);

// constants
const int DELETE_WG = 100;
const int RETRIEVE_WG = 101;
const int STORE_WG = 102;
const int SEND_ID = 103;
const int TERMINATE_SERVICE = 200;
#endif