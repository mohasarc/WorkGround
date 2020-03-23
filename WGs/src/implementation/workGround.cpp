// author : Mohammed S. Yaseen
// date   : 5/1/2020

#include "..\header\workGround.h"
#include <iostream>
using namespace std;

WorkGround::WorkGround(){
	wgName = "";
	taskNo = 0;
	head   = NULL;
}

WorkGround::WorkGround(string awgName){
	// cout<<"\nwgconst\n";
	wgName = awgName;
	taskNo = 0;
	head   = NULL;
}

WorkGround::~WorkGround(){
	while(head){
		taskNode* tmp = head;
		head = head->next;
		delete tmp;
	}
}

WorkGround::WorkGround(const WorkGround &toCopy){
	wgName = toCopy.wgName;
	taskNo = toCopy.taskNo;
	wgID = toCopy.wgID;

	if(toCopy.head == NULL){
		// if toCopy tasks list is empty
		head = NULL;
	} else{
		// copy the head
		head = new taskNode;
		head->task = toCopy.head->task;
		// pointing to the head
		taskNode* prev = head;

		// copy other nodes
		for(taskNode* cur = toCopy.head->next; cur != NULL; cur = cur->next){
			prev->next = new taskNode;
			prev = prev->next;
			prev->task = cur->task;
		}

		// put the next of the last to NULL
		if(prev != NULL)
			prev->next = NULL;
	}
}

void WorkGround::operator=(const WorkGround &rhs){
	wgName = rhs.wgName;
	taskNo = rhs.taskNo;
	wgID = rhs.wgID;

	// delete all current nodes
	while(head){
		taskNode* tmp = head;
		head = head->next;
		delete tmp;
	}

	if(rhs.head == NULL){
		// if rhs tasks list is empty
		head = NULL;
	} else{
		// copy the head
		head = new taskNode;
		head->task = rhs.head->task;
		// pointing to the head
		taskNode* prev = head;

		// copy other nodes
		for(taskNode* cur = rhs.head->next; cur != NULL; cur = cur->next){
			prev->next = new taskNode;
			prev = prev->next;
			prev->task = cur->task;
		}

		// put the next of the last to NULL
		if(prev != NULL)
			prev->next = NULL;
	}
}

bool WorkGround::addTask(Task task){
	taskNode* last = NULL;
	if (task.getTaskName() == "") {
		return false;
	}

	// traverse till the last node
	for (taskNode* cur = head; cur != NULL; cur = cur->next) {
		last = cur;
		if (cur->task.getTaskName() == task.getTaskName()) {
			return false;
		}
	}

	taskNode* tmp = new taskNode;
	tmp->task = task;
	tmp->next = NULL;

	if (last != NULL)
		last->next = tmp;
	else
		head = tmp;
	taskNo++;
	return true;
}

bool WorkGround::removeTask(const string taskName){
	if (head == NULL){
		return false;
	} 

	if (taskName != ""){
		taskNode* cur = NULL;
		taskNode* prev = NULL;
		for(cur = head; cur != NULL && cur->task.getTaskName() != taskName; cur = cur->next){
			prev = cur;
		}

		if (cur != NULL && prev != NULL){
			//cout<<"cur is not null!!!!"<<endl;
			prev->next = cur->next;
			delete cur;
			taskNo--;
			return true;

		} else if (cur != NULL && prev == NULL){
			// the head is the targeted node
			taskNode* tmp = cur;
			head = head->next;
			delete tmp; 
			taskNo--;
			return true;
		} else 
			return false;
	}

	return false;
}

bool WorkGround::removeTask(const int taskIndex) {
	if (head == NULL) {
		return false;
	}

	// Check if valid index
	if (taskIndex < taskNo && taskIndex >= 0) {
		taskNode* cur = NULL;
		taskNode* prev = NULL;
		int i = 0;
		for (cur = head; cur != NULL && i != taskIndex; cur = cur->next) {
			prev = cur;
			i++;
		}

		if (cur != NULL && prev != NULL) {
			//cout<<"cur is not null!!!!"<<endl;
			prev->next = cur->next;
			delete cur;
			taskNo--;
			return true;

		}
		else if (cur != NULL && prev == NULL) {
			// the head is the targeted node
			taskNode* tmp = cur;
			head = head->next;
			delete tmp;
			taskNo--;
			return true;
		}
		else
			return false;
	}

	return false;
}

bool WorkGround::renameWorkGround(const string awgName){
	if (awgName != ""){
		wgName = awgName;
		return true;
	}

	return false;
}

bool WorkGround::run(){
	bool successReport = true;
	bool enteredLoop   = false;

	if(head != NULL){
		for (taskNode* cur = head; cur != NULL; cur = cur->next){
			successReport = successReport && cur->task.run();
			enteredLoop   = true;
		}
	}

	return successReport && enteredLoop;
}

string WorkGround::getWgName(){
	if (wgName != ""){
		return wgName;
	} else 
		return "Error: the WorkGround has no name.";
}

string WorkGround::wgView(){
	string s = "";
	string p = "";
	int order = 0;

	if (head != NULL){
		s = s + wgName + "\n\tTasks :\n";
		for (taskNode* cur = head; cur != NULL; cur = cur->next){
			order++;

			for (int i = 0; i < cur->task.getAppPath().length(); i++){
				p += cur->task.getAppPath()[i];

				if( i % 30 == 0 && i != 0)
					p += "\n\t\t\t   ";
			}

			// string orderstr = order;
			string orderS = std::to_string(order);
			s = s + "\t" + orderS + " - " + cur->task.getTaskName()
				  + "\n\t\tApp Path : " + p;

			int size;
			string* taskFiles = cur->task.getFilesPaths(size);
			
			if (taskFiles != NULL){
				for(int i = 0; i < size; i++){
					s = s + "\n\t\t + " + taskFiles[i];
				}

				delete []taskFiles;
				taskFiles = NULL;
			}

			p = "";
			s = s + "\n";
		}

		return s;
	}

	return "The Work Ground is empty\n";
}

Task* WorkGround::findTask(const string taskName){
	Task* tmpTask;
	for(taskNode* cur = head; cur != NULL; cur = cur->next)
		if(cur->task.getTaskName() == taskName){
			tmpTask = &cur->task;
			return tmpTask;
		}

	return NULL;
}

//bool WorkGround::getTask(string taskName, Task*& theTask) {
//	for (taskNode* cur = head; cur != NULL; cur = cur->next)
//		if (cur->task.getTaskName() == taskName) {
//			tmpTask = &cur->task;
//			return tmpTask;
//		}
//
//	return NULL;
//}

ostream& operator<<(ostream& out, const WorkGround& toSave) {
	out << toSave.wgName << "\n" << toSave.taskNo << "\n" << toSave.wgID;
	
	WorkGround::taskNode* cur;
	for (cur = toSave.head; cur != NULL; cur = cur->next) {
		out << "\n" << cur->task;
	}
	return out;
}

istream& operator>>(istream& in, WorkGround& retrieved) {
	string taskNo;
	string wgIDStr;
	getline(in, retrieved.wgName, '\n');
	getline(in, taskNo);
	getline(in, wgIDStr);
	retrieved.wgID = stoi(wgIDStr);

	Task* tmp;
	for (int i = 0; i < stoi(taskNo); i++) {
		tmp = new Task();
		in >> *tmp;
		retrieved.addTask(*tmp);
	}
	return in;
}

vector<string> WorkGround::getTaskPath() {
	taskNode* cur = head;
	vector<string> taskPaths;
	for (; cur != NULL; cur = cur->next) {
		taskPaths.push_back(cur->task.getAppPath());
	}
	return taskPaths;
}

bool WorkGround::close() {	// Depricated // Not reliable
	string taskName, taskNamePath;
	string killName;
	int index = 0;
	int sysFeedBack = -1;
	taskNode* cur = head;
	
	for (; cur != NULL; cur = cur->next) {
		taskNamePath = cur->task.getAppPath();
		for (int j = 0; j < taskNamePath.length(); j++) {
			if (taskNamePath[j] == '\\')
				index = j + 1;
		}
		taskName = taskNamePath.substr(index, taskNamePath.length() - 2);
		killName = "taskkill /IM " + taskName;
		sysFeedBack = system(killName.c_str());
	}

	if (sysFeedBack == 0)
		return true;
	else
		return false;
}

bool WorkGround::hTerminate() {
	bool success = true;

	if (taskNo <= 0)
		return false;

	for (taskNode* cur = head; cur != NULL; cur = cur->next) {
		success = success && cur->task.hTerminate();
	}

	return success;
} 

void WorkGround::setID(int id) {
	wgID = id;
}

int WorkGround::getID() {
	return wgID;
}

bool WorkGround::serialize(WorkGround toSerialize, string &serialized) {
	serialized += toSerialize.wgName 
			   + "\n" + to_string( toSerialize.taskNo ) 
			   + "\n" + to_string( toSerialize.wgID );

	WorkGround::taskNode* cur;
	for (cur = toSerialize.head; cur != NULL; cur = cur->next) {
		serialized += "\n";
		Task::serialize(cur->task, serialized);
	}

	return true;
}

bool WorkGround::deserialize(stringstream &toDeserialize, WorkGround* deserialized) {
	string taskNo;
	string wgIDStr;
	getline(toDeserialize, deserialized->wgName, '\n');
	getline(toDeserialize, taskNo);
	getline(toDeserialize, wgIDStr);
	deserialized->wgID = stoi(wgIDStr);

	Task* tmp;
	for (int i = 0; i < stoi(taskNo); i++) {
		tmp = new Task();
		Task *temp = new Task();
		Task::deserialize(toDeserialize, *temp);
		deserialized->addTask(*temp);
	}
	return true;
}

bool WorkGround::filter(string filterSequence) {
	map<int, int> parsedSequence;
	pair<map<int, int>::iterator, bool> ret;
	bool
	bParsePange = parseRange(filterSequence.substr(1, filterSequence.size() - 1), parsedSequence);

	// invalid sequence
	if (!bParsePange)
		return false;

	// These are the tasks to keep
	if (filterSequence[0] == '+') {
		for (int i = 0; i < taskNo; i++) {
			ret = parsedSequence.insert(pair<int, int>(i, 0));
			// If could add the number -> it didn't exist then delete the task
			// at that location
			if (ret.second)
				removeTask(i - 1);
		}
	}
	// These are the tasks to remove
	else if (filterSequence[0] == '-') {
		for (pair<int, int> i : parsedSequence) {
			removeTask(i.first - 1);
		}
	}
	// Any other char at index 0 in invalid
	else
		return false;
}
