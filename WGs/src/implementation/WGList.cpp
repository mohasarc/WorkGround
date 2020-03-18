#include "..\header\WGList.h"

WGList::WGList() {}

WGList::~WGList() {}

WGList::WGList(const WGList &toCopy) {
	for (unsigned i = 0; i < wgs.size(); i++)
		*wgs[i] = *toCopy.wgs[i];
}

void WGList::operator=(WGList& rhs) {
	for (unsigned i = 0; i < wgs.size(); i++)
		*wgs[i] = *rhs.wgs[i];
}

string WGList::viewWG() {
	string wgInfoTmp;
	unsigned itemPerLine = 4;
	// view WorkGrounds' names
	wgInfoTmp = string("\n--------------------------------------------------\n") +
						 "                  WORKGROUNDS LIST                \n" +
						 "--------------------------------------------------\n";
	if (wgs.size() <= 0)
		wgInfoTmp += "\nThere are no WorkGrounds yet to be viewed\n";
	else
		for (int i = 0; i < wgs.size(); i++) {
			wgInfoTmp += wgs[i]->getWgName() + " ( " + to_string(wgs[i]->getID()) + " ) " + "\t";
			if (i != 0 && (i + 1) % itemPerLine == 0) // to print a number of items per line
				wgInfoTmp += "\n";
		}
	return wgInfoTmp;
}

string WGList::viewWgElab(string wgName) {
	bool found = false;
	string wgInfoTmp;
	// view WorkGrounds' details
	wgInfoTmp = string("\n--------------------------------------------------\n") +
						 "                  WORKGROUNDS LIST                \n" +
						 "--------------------------------------------------\n";
	if (wgs.size() <= 0)
		wgInfoTmp += "\nThere are no WorkGrounds yet to be viewed\n";
	else
		for (int i = 0; i < wgs.size() && !found; i++) {
			if (wgName == "*") { // view all
				wgInfoTmp += wgs[i]->wgView();

			} else if (wgs[i]->getWgName() == wgName) {
				wgInfoTmp += wgs[i]->wgView();
				found = true;
			}
		}
	if (!found && wgName != "*" && wgs.size() > 0) {
		wgInfoTmp += "\n There is no WorkGround with the name : " + wgName + "\n";
	}
	return wgInfoTmp;
}

bool WGList::addWg(const string wgName) {
	WorkGround* tmpWg = findWg(wgName);

	if (tmpWg != NULL | wgName == "")
		return false;
	else {
		WorkGround* newWG = new WorkGround(wgName);
		newWG->setID( generateWGID() );
		wgs.push_back(newWG);

		return true;
	}
}

bool WGList::removeWg(const string wgName) {
	WorkGround* tmpWg = findWg(wgName);

	for (unsigned i = 0; i < wgs.size(); i++) {
		if (wgs[i]->getWgName() == wgName) {
			wgs.erase(wgs.begin() + i);
			return true;
		}
	}

	return false;
}

bool WGList::renameWg(const string oldWgName, const string newWgName) {
	WorkGround* tmpWg = findWg(oldWgName);
	WorkGround* tmpWg2 = findWg(newWgName);

	if (tmpWg == NULL | tmpWg2 != NULL)
		return false;
	else {
		tmpWg->renameWorkGround(newWgName);
		return true;
	}
}

bool WGList::addTask(const string wgName, const string taskName, const string taskPath) {
	WorkGround* tmpWg = findWg(wgName);
	if (tmpWg == NULL)
		return false;
	else {
		Task task(taskName, taskPath);
		return tmpWg->addTask(task);
	}
}

bool WGList::removeTask(const string wgName, const string taskName) {
	WorkGround* tmpWg = findWg(wgName);
	if (tmpWg == NULL)
		return false;
	else {
		return tmpWg->removeTask(taskName);
	}
}

bool WGList::renameTask(const string wgName, const string oldTaskName, const string newTaskName) {
	WorkGround* tmpWg = findWg(wgName);
	if (tmpWg == NULL)
		return false;
	else {
		Task* taskPtr = tmpWg->findTask(oldTaskName);
		Task* taskPtr2 = tmpWg->findTask(newTaskName);
		if (taskPtr == NULL | taskPtr2 != NULL)
			return false;
		else {
			taskPtr->renameTask(newTaskName);
			return true;
		}
	}
}

bool WGList::addFile(const string wgName, const string taskName, const string fileName, const string filePath) {
	WorkGround* tmpWg = findWg(wgName);
	if (tmpWg == NULL)
		return false;
	else {
		Task* taskPtr;
		taskPtr = tmpWg->findTask(taskName);
		if (taskPtr != NULL) {
			return taskPtr->addFile(filePath, fileName);
		}
		return false;
	}
}

bool WGList::removeFile(const string wgName, const string taskName, const string fileName) {
	WorkGround* tmpWg = findWg(wgName);
	if (tmpWg == NULL)
		return false;
	else {
		Task* taskPtr;
		taskPtr = tmpWg->findTask(taskName);
		if (taskPtr != NULL) {
			return taskPtr->removeFile(fileName);
		}
		return false;
	}
}

bool WGList::renameFile(const string wgName, const string taskName, const string oldFilaName, const string newFileName) {
	WorkGround* tmpWg = findWg(wgName);
	if (tmpWg == NULL)
		return false;
	else {
		Task* taskPtr;
		taskPtr = tmpWg->findTask(taskName);
		if (taskPtr == NULL)
			return false;
		else {
			return taskPtr->renameFile(oldFilaName, newFileName);
		}
	}
}

bool WGList::runWG(const string wgName) {
	WorkGround* tmpWg = findWg(wgName);
	if (tmpWg == NULL)
		return false;
	else {
		return tmpWg->run();
	}
}

WorkGround* WGList::findWg(string wgName) {
	WorkGround* tmpWG;
	for (unsigned i = 0; i < wgs.size(); i++) {
		if (wgs[i]->getWgName() == wgName) {
			tmpWG = wgs[i];
			return tmpWG;
		}
	}
	// if not found
	return NULL;
}

Task* WGList::findTask(string wgName, string taskName) {
	WorkGround* tmpWg = findWg(wgName);
	Task* tmpTask;

	if (tmpWg == NULL) // if not found
		return NULL;
	else {
		tmpTask = tmpWg->findTask(taskName);
		return tmpTask;
	}
}

ostream& operator<<(ostream& out, const WGList& toSave) {
	out << toSave.wgs.size();

	for (int i = 0; i < toSave.wgs.size(); i++) {
		out << "\n" << *toSave.wgs[i];
	}
	out << endl;
	return out;
}

istream& operator>>(istream& in, WGList& retrieved) {
	string wgNo;
	getline(in, wgNo, '\n');

	WorkGround* tmp;
	for (int i = 0; i < stoi(wgNo); i++) {
		tmp = new WorkGround();
		in >> *tmp;
		retrieved.wgs.push_back(tmp);
	}
	return in;
}

int WGList::switchWg(string wgToClose, string wgToRun) {
	WorkGround* wgToCloseTask = NULL;
	WorkGround* wgToRunTask = NULL;
	bool runSuccess = false;
	bool closeSuccess = false;

	// finding the workground to close and the one to open
	for (int z = 0; z < wgs.size(); z++) {
		if (wgs[z]->getWgName() == wgToClose) {
			wgToCloseTask = wgs[z];
		}
		if (wgs[z]->getWgName() == wgToRun) {
			wgToRunTask = wgs[z];
		}
	}
	if (wgToCloseTask)
		closeSuccess = wgToCloseTask->close();		// should be changed to hTerminate
	if (wgToRunTask) {
		runSuccess = wgToRunTask->run();

	}

	if (closeSuccess && runSuccess)
		return 0; // one closed and one run
	else if (closeSuccess && !runSuccess)
		return 1;
	else if (!closeSuccess && !runSuccess)
		return -1; // did nothing
}

int WGList::generateWGID() {
	map<int, string> wgsMap;
	cout << "generate ID is called " << endl;
	cout << "size is " << wgs.size() << endl;
	if (wgs.size() == 0)
		return 0;

	for (int i = 0; i < wgs.size(); i++) {
		cout << "adding the key " << wgs[i]->getID() << endl;
		wgsMap[wgs[i]->getID()] = wgs[i]->getWgName();
	}

	for (int j = 0; j <= wgs.size(); j++) {
		pair<map<int, string>::iterator, bool> mapReturn;
		mapReturn = wgsMap.insert(pair<int, string>(j, "test"));

		if (mapReturn.second == true) {
			cout << "id is : " << j << endl;
			return j;
		}
	}
}

// ****************************************
// Functions to comunicate with wgbgservice
// ****************************************

// To store a currently active wg in memory
bool WGList::storeToMem(HANDLE hPipe, WorkGround activeWG) {
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
bool WGList::retrieveFromMem(HANDLE hPipe, string wgName, WorkGround& WGtoTerminate) {
	// Local Variables
	WorkGround* wgBuffer;
	DWORD wgBufferSize = sizeof(wgBuffer);
	DWORD dwNoBytesRead;
	bool bReadFile;

	// calculate the sum

	// send WorkGround name
	string astr = "";
	string* wgNameBuffer = &astr;
	DWORD wgNameBufferSize;
	DWORD dwNoBytesWrite;
	bool bWriteFile;

	bWriteFile = WriteFile(
		hPipe,
		wgNameBuffer,
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
		cout << "ReadFile Failed & Error No - " << GetLastError() << endl;
	}
	else
	{
		cout << "success reading" << endl;
		
	}
}

// To start wgbgservice if not already active
bool WGList::startService() {
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
bool WGList::connect(HANDLE &hPipe) {

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
bool WGList::IsProcessRunning(const TCHAR* const executableName) {
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