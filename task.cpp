#include "task.h"
#include <windows.h>
#include <iostream>
// constructor
Task::Task(string ataskName, string aappPath){
	taskName = ataskName;
	appPath = appPath;
	head = NULL;
	fileNo = 0;
}

// copy constructor
Task::~Task(const Task &toCopy){
	taskName = toCopy.taskName;
	appPath  = toCopy.appPath;

	// delete all current nodes
	while(head){
		fileNode* tmp = head;
		head = head->next;
		delete tmp;
	}

	if(toCopy.head == NULL){
		// if toCopy files list is empty
		head = NULL
	} else{
		// copy the head
		head = new fileNode;
		head->fileNickName = toCopy.head->fileNickName;
		head->filePath     = toCopy.head->filePath;
		// pointing to the head
		fileNode* prev = head;

		// copy other nodes
		for(fileNode cur = toCopy.head->next; cur != NULL; cur = cur->next){
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

	// delete all current nodes
	while(head){
		fileNode* tmp = head;
		head = head->next;
		delete tmp;
	}

	if(rhs.head == NULL){
		// if rhs files list is empty
		head = NULL
	} else{
		// copy the head
		head = new fileNode;
		head->fileNickName = rhs.head->fileNickName;
		head->filePath     = rhs.head->filePath;
		// pointing to the head
		fileNode* prev = head;

		// copy other nodes
		for(fileNode cur = rhs.head->next; cur != NULL; cur = cur->next){
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
	if(afilePath == "" | afileNickName == ""){
		return false;
	}

	if(head != NULL){
		// traverse till the last node
		fileNode last;
		for(last = head; last->next != NULL; last = last->next);
		fileNode* tmp = new fileNode;
		tmp->fileNickName = afileNickName;
		tmp->filePath = afilePath;
		tmp->next = NULL;
		last->next = tmp;
		return true;

	} else {
		head = new fileNode;
		head->fileNickName = afileNickName;
		head->filePath = afilePath;
		head->next = NULL;
		return true;
	}
}

bool Task::removeFile(string afileNickName){
	if (head == NULL){
		return false;
	}

	if (afileNickName != ""){
		fileNode* cur;
		fileNode* prev;
		for(cur = head; cur->fileNickName != afileNickName; cur = cur->next){
			prev = cur;
		}

		if (cur != NULL){
			prev->next = cur->next;
			delete cur;
			return true;

		} else
			false;
	} else 
		return false;
}

bool Task::changeApp(string aappPath){
	appPath = aappPath;
}

bool Task::run(){
	STARTINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	bool processSuccess = NULL;

	string cmdCommandStr = appPath;
	if(head != NULL){
		for (fileNode cur = head; cur != NULL; cur = cur->next)
			cmdCommandStr += " " + cur->filePath;
	}

	char cmdCommandChr[] = cmdCommandStr;

	CreateProcessA(
		NULL,
		cmdCommandChr,
		NULL,
		NULL,
		false,
		0,
		NULL,
		NULL,
		&si,
		&pi
		);

	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );
}

//