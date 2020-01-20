#ifndef APP_H
#define APP_H

#include <iostream>
#include <vector> 
#include "task.h"
#include "WorkGround.h"
using namespace std;

class WGList {
public:
	WGList(WGList& toCopy);
	void operator=(WGList& rhs);

	string viewWG();
	string viewWgElab();
	bool addWg(const string wgName);
	bool removeWg(const string wgName);
	bool renameWg(const string oldWgName, const string newWgName);
	bool addTask(const string wgName, const string taskName, const string taskPath);
	bool removeTask(const string wgName, const string taskName);
	bool renameTask(const string wgName, const string oldTaskName, const string newTaskName);
	bool addFile(const string wgName, const string taskName, const string filaName, const string filePath);
	bool removeFile(Task& task, const string filaName);
	bool renameFile(Task& task, const string oldFilaName, const string newFileName);
	WorkGround* findWg(string wgName);
	Task* findTask(string wgName, string taskName);
private:
	vector<WorkGround*> wgs;
};
#endif