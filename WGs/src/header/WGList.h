// author : Mohammed S. Yaseen
// date   : 5/1/2020

#ifndef WGLIST_H
#define WGLIST_H

#include <vector> 
#include "task.h"
#include "WorkGround.h"
using namespace std;

class WGList{
public:
	WGList();
	~WGList();
	WGList(const WGList& toCopy);
	void operator=(WGList& rhs);
	string viewWG();
	string viewWgElab(string wgName);
	bool addWg(const string wgName);
	bool removeWg(const string wgName);
	bool renameWg(const string oldWgName, const string newWgName);
	bool switchWg(string wgRunning, string wgToRun);
	bool addTask(const string wgName, const string taskName, const string taskPath);
	bool removeTask(const string wgName, const string taskName);
	bool renameTask(const string wgName, const string oldTaskName, const string newTaskName);
	bool addFile(const string wgName, const string taskName, const string filaName, const string filePath);
	bool removeFile(const string wgName, const string taskName, const string filaName);
	bool renameFile(const string wgName, const string taskName, const string oldFilaName, const string newFileName);
	bool runWG(const string wgName);
	WorkGround* findWg(string wgName);
	Task* findTask(string wgName, string taskName);
	friend ostream& operator<<(ostream& out, const WGList& toSave);
	friend istream& operator>>(istream& in, WGList& retrieved);
private:
	vector<WorkGround*> wgs;
};
#endif