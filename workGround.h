#ifndef WORKGROUND_H
#define WORKGROUND_H
#include <string>
#include "task.h"
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
private:
struct taskNode{
	Task task;
	taskNode* next;
};

string wgName;
taskNode* head;
};
	
	
	
#endif