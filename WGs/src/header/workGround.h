// author : Mohammed S. Yaseen
// date   : 5/1/2020

#ifndef WORKGROUND_H
#define WORKGROUND_H
#include "task.h"
using namespace std;

class WorkGround{
public:
	WorkGround();
	WorkGround(string awgName);
	WorkGround(const WorkGround &toCopy);
	~WorkGround();
	void operator=(const WorkGround &rhs);
	bool renameWorkGround(const string wgName);
	bool addTask(Task atask);
	bool removeTask(const string taskNickName);
	Task* WorkGround::findTask(const string taskName);
	string getWgName();
	string wgView();
	bool run();
private:
struct taskNode{
	Task task;
	taskNode* next;
};

string wgName;
taskNode* head;
};

#endif