#ifndef WORKGROUND_H
#define WORKGROUND_H
class WorkGround(){
public:
	WorkGround();
	WorkGround(string awgName);
	WorkGround(const WorkGround &toCopy);
	~WorkGround();
	void operator=(const WorkGround &rhs);
	bool addTask(Task atask);
	bool removeTask(string taskNickName);
	bool renameWorkGround(string wgName);
private:
struct taskNode{
	Task task;
	taskNode next;
}

string wgName;
};
	
	
	
#endif