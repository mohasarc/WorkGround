// author : Mohammed S. Yaseen
// date   : 5/1/2020

#include "workGround.h"
#include <iostream>
using namespace std;

WorkGround::WorkGround(){
	wgName = "";
	head   = NULL;
}

WorkGround::WorkGround(string awgName){
	cout<<"\nwgconst\n";
	wgName = awgName;
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

	// delete all current nodes
	while(head){
		taskNode* tmp = head;
		head = head->next;
		delete tmp;
	}

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
	// if(task == NULL){
	// 	return false;
	// }

	cout<<"ading Task\n";

	if(head != NULL){
		// traverse till the last node
		taskNode* last;
		for(last = head; last->next != NULL; last = last->next);
		taskNode* tmp = new taskNode;
		tmp->task = task;
		tmp->next = NULL;
		last->next = tmp;
		return true;

	} else {
		head = new taskNode;
		head->task = task;
		head->next = NULL;
		return true;
	}
}

bool WorkGround::removeTask(string taskName){
	if (head == NULL){
		return false;
	}

	if (taskName != ""){
		taskNode* cur;
		taskNode* prev;
		for(cur = head; cur->task.getTaskName() != taskName; cur = cur->next){
			prev = cur;
		}

		if (cur != NULL){
			prev->next = cur->next;
			delete cur;
			return true;

		} else
			false;
	} else 
		return false;
}

bool WorkGround::renameWorkGround(string awgName){
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
		cout<<"head != NULL"<<endl;
		for (taskNode* cur = head; cur != NULL; cur = cur->next){
			cout<<"\n trying to run\t" << cur->task.getTaskName()<<endl;
			successReport = successReport && cur->task.run();
			enteredLoop   = true;
		}
	}

	return successReport && enteredLoop;
}

string wgView(){
	string s = "";
	int order = 0;

	if (head != NULL){
		s = s + "Tasks :\n"
		for (taskNode* cur = head; cur != NULL; cur = cur->next){
			order++;
			s = s + "\t" + order + " - " + cur->task.getTaskName()
				  + "\n\t\tApp Path : " + cur->task.getAppPath();

			int size;
			string* taskFiles = cur->task.getFilesPaths(size);
			for(int i = 0; i < size; i++){
				s = s + "\n\t\t + " + taskFiles[i];
			}
		}

		s = s + "\n";
		return s;
	}

	return "The Work Ground is empty\n";
}