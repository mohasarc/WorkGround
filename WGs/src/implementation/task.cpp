// author : Mohammed S. Yaseen
// date   : 5/1/2020

#include "..\header\task.h"

bool static runTask(const char* cmd) {
	
	STARTUPINFOA si;
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.wShowWindow = 0;

	PROCESS_INFORMATION pi;
	memset(&pi, 0, sizeof(PROCESS_INFORMATION));

	if (!CreateProcessA(
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
	))
	{
		return false;
	}

	return true;
}

Task::Task(){
	taskName = "";
	appPath = "";
	head = NULL;
	fileNo = 0;
}

// constructor
Task::Task(string ataskName, string aappPath){
	// cout<<"constructor"<<endl;
	taskName = ataskName;
	appPath = aappPath;
	head = NULL;
	fileNo = 0;
}

Task::~Task(){
	while(head){
		fileNode* tmp = head;
		head = head->next;
		delete tmp;
	}
}

// copy constructor
Task::Task(const Task &toCopy){
	// cout<<"\n copy const \n";

	taskName = toCopy.taskName;
	appPath  = toCopy.appPath;
	fileNo   = toCopy.fileNo;

	if(toCopy.head == NULL){
		// if toCopy files list is empty
		head = NULL;
		// cout<<"to copy's head == NULL\n";
	} else{
		// cout<<"copying the head\n";
		// copy the head
		head = new fileNode;
		head->fileNickName = toCopy.head->fileNickName;
		head->filePath     = toCopy.head->filePath;
		// pointing to the head
		fileNode* prev = head;

		// copy other nodes
		for(fileNode* cur = toCopy.head->next; cur != NULL; cur = cur->next){
			prev->next = new fileNode;
			prev = prev->next;
			prev->fileNickName = cur->fileNickName;
			prev->filePath     = cur->filePath;
		}

		// put the next of the last to NULL
		if(prev != NULL)
			prev->next = NULL;
	}
}

void Task::operator=(const Task &rhs){
	taskName = rhs.taskName;
	appPath  = rhs.appPath;
	fileNo   = rhs.fileNo;

	// delete all current nodes
	while(head){
		fileNode* tmp = head;
		head = head->next;
		delete tmp;
	}

	if(rhs.head == NULL){
		// if rhs files list is empty
		head = NULL;
	} else{
		// copy the head
		head = new fileNode;
		head->fileNickName = rhs.head->fileNickName;
		head->filePath     = rhs.head->filePath;
		// pointing to the head
		fileNode* prev = head;

		// copy other nodes
		for(fileNode* cur = rhs.head->next; cur != NULL; cur = cur->next){
			prev->next = new fileNode;
			prev = prev->next;
			prev->fileNickName = cur->fileNickName;
			prev->filePath     = cur->filePath;
		}

		// put the next of the last to NULL
		if(prev != NULL)
			prev->next = NULL;
	}
}

bool Task::addFile(string afilePath, string afileNickName){
	fileNode* last = NULL;

	if(afilePath == "" | afileNickName == ""){
		return false;
	}

	// traverse till the last node
	for (fileNode* cur = head; cur != NULL; cur = cur->next) {
		last = cur;
		if (cur->filePath == afilePath | cur->fileNickName == afileNickName)
			return false;
	}

	fileNode* tmp = new fileNode;
	tmp->fileNickName = afileNickName;
	tmp->filePath = afilePath;
	tmp->next = NULL;
	if (last != NULL)
		last->next = tmp;
	else
		head = tmp;
	fileNo++;
	return true;
}

bool Task::removeFile(string afileNickName){
	if (head == NULL){
		return false;
	}

	if (afileNickName != ""){
		fileNode* cur = NULL;
		fileNode* prev = NULL;
		for(cur = head; cur != NULL && cur->fileNickName != afileNickName; cur = cur->next){
			prev = cur;
		}

		if (cur == head){ // the head is the one to be deleted
			head = head->next;
			delete cur;
		} else if (cur != NULL){
			prev->next = cur->next;
			delete cur;
			fileNo--;
			return true;
		} else
			false;
	} else 
		return false;
}

bool Task::changeApp(string aappPath){
	if(aappPath != ""){
		appPath = aappPath;
		return true;	
	}
	
	return false;
}

string Task::getTaskName(){
	return taskName;
}

bool Task::run(){

	string cmdCommandStr = appPath;
	if(head != NULL){
		for (fileNode* cur = head; cur != NULL; cur = cur->next)
			cmdCommandStr += " " + cur->filePath;
	}

	const char* cmdCommandChar = cmdCommandStr.c_str();
	return runTask(cmdCommandChar);
}

string* Task::getFilesPaths(int &size){
	string* pathArr = new string[fileNo];
	unsigned i = 0;
	string pathFormatted = "";

	if (head != NULL){
		for (fileNode* cur = head; cur != NULL; cur = cur->next){

			for (unsigned j = 0; j < cur->filePath.length(); j++){
				pathFormatted += cur->filePath[j];

				if( j % 30 == 0 && 1 != 0)
					pathFormatted += "\n\t\t\t   ";
			}

			pathArr[i] = cur->fileNickName 
						 + " : " 
						 + pathFormatted ;
			i++;
		}

		size = fileNo;
		return pathArr;
	}

	return NULL;
}

string Task::getAppPath(){
	return appPath;
}

bool Task::renameTask(string ataskName){
	taskName = ataskName;
	return true;
}

bool Task::renameFile(string oldFileName, string newFileName) {
	for (fileNode* cur = head; cur != NULL; cur = cur->next)
		if (cur->fileNickName == newFileName)
			return false; // new name has been used before

	for (fileNode* cur = head; cur != NULL; cur = cur->next) {
		if (cur->fileNickName == oldFileName) {
			cur->fileNickName = newFileName;
			return true;
		}
	}
	return false;
}

// Write the member variables to stream object
ostream& operator<<(ostream& out, const Task& toSave) {
	out << toSave.taskName << "\n" << toSave.appPath << "\n"
		<< toSave.fileNo;
	// adding files
	Task::fileNode* cur;
	for (cur = toSave.head; cur != NULL; cur = cur->next) {
		out << "\n" << cur->fileNickName;
		out << "\n" << cur->filePath;
	}
	return out;
}

// Read data from stream object and fill in member variables
istream& operator>>(istream& in, Task& retrieved) {
	int fileNo = 0;
	in >> retrieved.taskName;
	in >> retrieved.appPath;
	in >> fileNo;

	for (int i = 0; i < fileNo; i++) {
		string fileName, filePath;
		in >> fileName;
		in >> filePath;
		retrieved.addFile(filePath, fileName);
	}
	return in;
}