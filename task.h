#ifndef TASK_H
#define TASK_H

#include <string>

class Task{
public:
Task(string ataskName = "", string aappPath = "");
~Task();
Task(Task &toCopy);

bool addFile(string afilePath, string afileNickName);
bool removeFile(string afileNickName);
bool changeProgram(string aappPath);
bool run();

private:
struct fileNode{
	string fileNickName;
	string filePath;
	fileNode next;
}
string taskName;
string appPath;
fileNode* head;
};
#endif