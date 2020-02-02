// author : Mohammed S. Yaseen
// date   : 5/1/2020

#ifndef TASK_H
#define TASK_H

#include <string>
#include <windows.h>
#include <iostream>
#include <fstream>

using namespace std;

class Task{
public:
Task();
Task(string ataskName, string aappPath);
~Task();
Task(const Task &toCopy);
void operator=(const Task &rhs);
bool addFile(string afilePath, string afileNickName);
bool removeFile(string afileNickName);
bool changeApp(string aappPath);
bool renameTask(string ataskName);
bool renameFile(string oldFileName, string newFileName);
string* getFilesPaths(int &size);
string getAppPath();
string getTaskName();
bool run();
friend ostream& operator<<(ostream& out, const Task& toSave);
friend istream& operator>>(istream& in, Task& retrieved);

private:
struct fileNode{
	string fileNickName;
	string filePath;
	fileNode* next;
};
string taskName;
string appPath;
fileNode* head;
int fileNo;
};
#endif