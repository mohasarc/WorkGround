#ifndef TASK_H
#define TASK_H

#include <string>

class Task{
public:
Task(string taskName, string appPath);
~Task();
Task(Task toCopy);
bool addFile(string filePath, string fileNickName);
bool removeFile(string fileNickName);
bool changeProgram(string appPath);

private:
struct fileNode{
	string fileNickName;
	string filePath;
	fileNode next;
}
string taskName;
string appPath;
};
#endif