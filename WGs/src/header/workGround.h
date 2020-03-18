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
	bool renameWorkGround(const string wgName);
	bool addTask(Task atask);
	bool removeTask(const string taskNickName);
	Task* findTask(const string taskName);
	string getWgName();
	string wgView();
	bool run();
	friend ostream& operator<<(ostream& out, const WorkGround& toSave);
	friend istream& operator>>(istream& in, WorkGround& retrieved);
	vector<string> getTaskPath();
	bool close();
	bool hTerminate();
	void setID(int id);
	int getID();
private:
struct taskNode{
	Task task;
	taskNode* next;
};

string wgName;
int taskNo;
int wgID;
taskNode* head;
};

#endif