// ****************************************
// Functions to comunicate with wgbgservice
// ****************************************
// Author : Mohammed S. Yaseen
// Date	  :	18/03/2020
#include "..\header\connectService.h"

// To store a currently active wg in memory
bool storeToMem(HANDLE hPipe, WorkGround activeWG) {
	// Local Variables
	string serializedWG;
	char* serializedWGBuff = new char[BUFSIZE];
	DWORD serializedWGBuffSize = BUFSIZE;
	DWORD dwNoBytesWrite;
	bool bWriteFile;

	// Serialize the workground
	serializedWG = "";
	WorkGround::serialize(activeWG, serializedWG);
	// Initialize the buffer
	for (int i = 0; i < BUFSIZE; i++) {
		if (i < serializedWG.size()) {
			serializedWGBuff[i] = serializedWG.at(i);
		}
		else
			serializedWGBuff[i] = '\n';
	}

	sendRequest(hPipe, STORE_WG);

	// Write WorkGround object
	bWriteFile = WriteFile(
		hPipe,
		serializedWGBuff,
		serializedWGBuffSize,
		&dwNoBytesWrite,
		NULL );

	if (!bWriteFile) {
		cout << "Storing WG Failed & Error No - " << GetLastError() << endl;
		return false;
	} else {
		//cout << "Writing WG succeeded" << endl;
		//cout << "WG Sent \n" << activeWG.wgView();
		return true;
	}

	// Flush FileBuffer
	bool
	bFlushFileBuffer = FlushFileBuffers(hPipe);
	if (!bFlushFileBuffer) {
		cout << "FlushFile Buffer Failed & Error No - " << GetLastError() << endl;
	}
	else {
		//cout << "FlushFile Buffer Succeeded" << endl;
	}
}

// To retrieve a workground from memory to be terminated
bool retrieveFromMem(HANDLE hPipe, int wgID, WorkGround& WGtoTerminate) {
	// Local Variables
	char* serializedWgBuffer = new char[BUFSIZE];
	DWORD wgBufferSize = BUFSIZE;
	DWORD dwNoBytesRead;
	bool bReadFile;
	string serializedWG;
	WorkGround *retrievedWg;

	// Send OPcode
	sendRequest(hPipe, SEND_ID);

	// send WorkGround id
	DWORD wgIDBufferSize = sizeof(wgID);
	DWORD dwNoBytesWrite;
	bool bWriteFile;

	bWriteFile = WriteFile(
		hPipe,
		&wgID,
		wgIDBufferSize,
		&dwNoBytesWrite,
		NULL );

	if (!bWriteFile){
		cout << "Sending wgID Failed & Error No - " << GetLastError() << endl;
	} else {
		//cout << "WriteFile wgID succeeded" << endl;
	}

	// Send OPcode
	connect(hPipe);	// To tell the service to listen
	sendRequest(hPipe, RETRIEVE_WG);

	// ReadFile: retrieve the WorkGround
	bReadFile = ReadFile(
		hPipe,
		serializedWgBuffer,
		wgBufferSize,
		&dwNoBytesRead,
		NULL );
	if (!bReadFile) {
		cout << "Retrieving WorkGround Failed & Error No - " << GetLastError() << endl;
	} else {
		// Move data from buffer to a string
		serializedWG = "";
		for (int i = 0; i < BUFSIZE - 1; i++) {
			if (serializedWgBuffer[i] == '\n' && serializedWgBuffer[i + 1] == '\n')
				break;
			serializedWG += serializedWgBuffer[i];
		}

		// initialize a string stream with the data from the string
		stringstream serializedWGSstream(serializedWG);
		retrievedWg = new WorkGround();
		// deserialize the data in the string stream
		WorkGround::deserialize(serializedWGSstream, retrievedWg);
		WGtoTerminate = *retrievedWg;

		//cout << "Success wg reading" << endl;
		//cout << WGtoTerminate.wgView() << endl;
	}

	connect(hPipe);
	sendRequest(hPipe, DELETE_WG);

	return bWriteFile && bReadFile;
}

// To start wgbgservice if not already active
bool startService() {
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
		//cout << "Already running";
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
bool connect(HANDLE& hPipe) {

	// Delay 800 ms not to get error 231 - ERROR_PIPE_BUSY
	Sleep(800);

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
		//cout << "File Creation Succeded" << endl;
		return true;
	}
}

// To send the OPCode value to wgbgservice
bool sendRequest(HANDLE hPipe,int requestCode) {
	int locOpCode = requestCode;
	int* opCodeBuffer = &locOpCode;
	DWORD dwNoBytesWrite;
	bool
	bWriteFile = WriteFile(
		hPipe,
		opCodeBuffer,
		sizeof(requestCode),
		&dwNoBytesWrite,
		NULL);

	if (!bWriteFile) {
		cout << "Request sending Failed & Error No - " << GetLastError() << endl;
		return false;
	}
	else {
		//cout << "Request sent successfully" << endl;
		return true;
	}
}

// Checks whether a process with executableName is already running
bool IsProcessRunning(const TCHAR* const executableName) {
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

bool terminateService(HANDLE hPipe) {	// Needs improve (currently is service is not running it will run it then terminate it )
	const TCHAR* exeName = TEXT("wgbgservice.exe");
	if (IsProcessRunning(exeName)) {
		sendRequest(hPipe, TERMINATE_SERVICE);
		return true;
	}

	return false;
}