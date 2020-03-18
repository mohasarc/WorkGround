// ****************************************
// Functions to comunicate with wgbgservice
// ****************************************
// Author : Mohammed S. Yaseen
// Date	  :	18/03/2020

#include "connectService.h"

// To store a currently active wg in memory
bool static storeToMem(HANDLE hPipe, WorkGround activeWG) {
	// Local Variables
	WorkGround* wgBuffer = &activeWG;
	DWORD wgBufferSize = sizeof(activeWG);
	DWORD dwNoBytesWrite;
	bool bWriteFile;

	bWriteFile = WriteFile(
		hPipe,
		wgBuffer,
		wgBufferSize,
		&dwNoBytesWrite,
		NULL
	);
	if (!bWriteFile)
	{
		cout << "WriteFile Failed & Error No - " << GetLastError() << endl;
		return false;
	}
	else
	{
		cout << "WriteFile succeeded" << endl;
		return true;
	}
}

// To retrieve a workground from memory to be terminated
bool static retrieveFromMem(HANDLE hPipe, int wgID, WorkGround& WGtoTerminate) {
	// Local Variables
	WorkGround* wgBuffer;
	DWORD wgBufferSize = sizeof(WorkGround);
	DWORD dwNoBytesRead;
	bool bReadFile;

	// send WorkGround id
	int* wgIDBuffer = &wgID;
	DWORD wgIDBufferSize = sizeof(wgID);
	DWORD dwNoBytesWrite;
	bool bWriteFile;

	bWriteFile = WriteFile(
		hPipe,
		wgIDBuffer,
		wgIDBufferSize,
		&dwNoBytesWrite,
		NULL
	);
	if (!bWriteFile)
	{
		cout << "WriteFile wgID Failed & Error No - " << GetLastError() << endl;
		return false;
	}
	else
	{
		cout << "WriteFile wgID succeeded" << endl;
		return true;
	}

	// ReadFile: retrieve the WorkGround
	bReadFile = ReadFile(
		hPipe,
		wgBuffer,
		wgBufferSize,
		&dwNoBytesRead,
		NULL
	);
	if (!bReadFile)
	{
		cout << "ReadFile wg Failed & Error No - " << GetLastError() << endl;
	}
	else
	{
		cout << "success wg reading" << endl;
		WGtoTerminate = *wgBuffer;
	}
}

// To start wgbgservice if not already active
bool static startService() {
	// run the server if not run already
	BOOL bIsRunning;
	BOOL bCreateProcess;
	const char* cmd = "\".\\wgbgservice.exe\"";
	STARTUPINFOA si;
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.wShowWindow = 0;
	PROCESS_INFORMATION pi;
	memset(&pi, 0, sizeof(PROCESS_INFORMATION));
	const TCHAR* exeName = TEXT("wgbgservice.exe");

	bIsRunning = IsProcessRunning(exeName);

	if (bIsRunning) {
		cout << "already running";
		return true;
	}
	else {
		bCreateProcess = CreateProcessA(
			NULL,
			(LPSTR)cmd,
			NULL,  //lpProcessAttributes
			NULL,  //lpThreadAttributes
			FALSE, //bInheritHandles
			DETACHED_PROCESS | CREATE_NO_WINDOW,
			NULL,  //lpEnvironment
			NULL,  //lpCurrentDirectory
			&si,   //lpStartupInfo
			&pi    //lpProcessInformation
		);

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		if (bCreateProcess)
			return true;
		else
			return false;
	}
}

// To create file and connect to service pipe
// returns a handle to the file to be written to
bool static connect(HANDLE& hPipe) {

	// CreateFile for pipe
	hPipe = CreateFile(
		TEXT("\\\\.\\pipe\\wgbgservice"),
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hPipe == INVALID_HANDLE_VALUE)
	{
		cout << "File Creation Failed & Error No - " << GetLastError() << endl;
		return false;
	}
	else
	{
		cout << "File Creation Succeded" << endl;
		return true;
	}
}

// Checks whether a process with executableName is already running
bool static IsProcessRunning(const TCHAR* const executableName) {
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (!Process32First(snapshot, &entry)) {
		CloseHandle(snapshot);
		return false;
	}

	do {
		if (!_tcsicmp(entry.szExeFile, executableName)) {
			CloseHandle(snapshot);
			return true;
		}
	} while (Process32Next(snapshot, &entry));

	CloseHandle(snapshot);
	return false;
}