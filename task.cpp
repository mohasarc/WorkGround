// author : Mohammed S. Yaseen
// date   : 5/1/2020

#include <bits/stdc++.h>
#include "task.h"
#include <windows.h>
#include <iostream>

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
	if(afilePath == "" | afileNickName == ""){
		return false;
	}

	if(head != NULL){
		// traverse till the last node
		fileNode* last;
		for(last = head; last->next != NULL; last = last->next);
		fileNode* tmp = new fileNode;
		tmp->fileNickName = afileNickName;
		tmp->filePath = afilePath;
		tmp->next = NULL;
		last->next = tmp;
		fileNo++;
		return true;

	} else {
		head = new fileNode;
		head->fileNickName = afileNickName;
		head->filePath = afilePath;
		head->next = NULL;
		fileNo++;
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
		for(cur = head; cur != NULL && cur->fileNickName != afileNickName; cur = cur->next){
			prev = cur;
		}

		cout<<afileNickName<<endl;

		if (cur == head){ // the head is the one to be deleted
			// cout<<"head to be deleted\n";
			head = head->next;
			delete cur;
		} else if (cur != NULL){
			// cout<<"cur is not null\n";
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
	// cout<<"running with " << appPath<<endl;

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	bool processSuccess = false;

	string cmdCommandStr = appPath;
	if(head != NULL){
		for (fileNode* cur = head; cur != NULL; cur = cur->next)
			cmdCommandStr += " " + cur->filePath;
	}

	char cmdCommandChr[cmdCommandStr.length() + 1];
	strcpy(cmdCommandChr, cmdCommandStr.c_str());

	processSuccess = CreateProcessA(
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

	// WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );

	return processSuccess;
}

string* Task::getFilesPaths(int &size){
	string* pathArr = new string[fileNo];
	int i = 0;
	string pathFormatted = "";


	if (head != NULL){
		for (fileNode* cur = head; cur != NULL; cur = cur->next){

			for (int i = 0; i < cur->filePath.length(); i++){
				pathFormatted += cur->filePath[i];

				if( i % 30 == 0 && 1 != 0)
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
//
