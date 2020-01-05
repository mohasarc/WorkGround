#ifndef TASK_H
#define TASK_H

#include <string>
using namespace std;

class Task{
public:
Task(string ataskName, string aappPath);
~Task();
Task(const Task &toCopy);
void operator=(const Task &rhs);
bool addFile(string afilePath, string afileNickName);
bool removeFile(string afileNickName);
bool changeApp(string aappPath);
bool run();

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