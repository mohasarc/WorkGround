// author : Mohammed S. Yaseen
// date   : 5/1/2020

#ifndef WORKGROUND_H
#define WORKGROUND_H
#include "task.h"
#include <vector>
using namespace std;

class WorkGround{
public:
	WorkGround();
	WorkGround(string awgName);
	WorkGround(const WorkGround &toCopy);
	~WorkGround();
	void operator=(const WorkGround &rhs);
	bool addTask(Task atask);
	bool removeTask(string taskNickName);
	bool renameWorkGround(string wgName);
	bool run();
	bool getTask(string taskName, Task* &theTask);
	string getWgName();
	string wgView();
	vector<string> getTaskPath();
	bool close();
private:
struct taskNode{
	Task task;
	taskNode* next;
};

string wgName;
taskNode* head;
};

#endif