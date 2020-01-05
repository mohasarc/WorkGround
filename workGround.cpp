#include <workGround.h>

workGround::workGround(){
	wgName = "";
	head   = NULL;
}

WorkGround::WorkGround(string awgName){
	wgName = awgName;
	head   = NULL;
}

workGround::~workGround(){
	while(head){
		TaskNode* tmp = head;
		head = head->next;
		delete tmp;
	}
}

workGround::workGround(const workGround &toCopy){
	wgName = toCopy.wgName;

	// delete all current nodes
	while(head){
		TaskNode* tmp = head;
		head = head->next;
		delete tmp;
	}

	if(toCopy.head == NULL){
		// if toCopy tasks list is empty
		head = NULL;
	} else{
		// copy the head
		head = new TaskNode;
		head->task = toCopy.head->task;
		// pointing to the head
		TaskNode* prev = head;

		// copy other nodes
		for(TaskNode* cur = toCopy.head->next; cur != NULL; cur = cur->next){
			prev->next = new TaskNode;
			prev = prev->next;
			prev->task = cur->task;
		}

		// put the next of the last to NULL
		if(prev != NULL)
			prev->next = NULL;
	}
}

void operator=(const workGround &rhs){
	wgName = rhs.wgName;

	// delete all current nodes
	while(head){
		TaskNode* tmp = head;
		head = head->next;
		delete tmp;
	}

	if(rhs.head == NULL){
		// if rhs tasks list is empty
		head = NULL;
	} else{
		// copy the head
		head = new TaskNode;
		head->task = rhs.head->task;
		// pointing to the head
		TaskNode* prev = head;

		// copy other nodes
		for(TaskNode* cur = rhs.head->next; cur != NULL; cur = cur->next){
			prev->next = new TaskNode;
			prev = prev->next;
			prev->task = cur->task;
		}

		// put the next of the last to NULL
		if(prev != NULL)
			prev->next = NULL;
	}
}

bool WorkGround::addTask(Task task){
	if(task == NULL){
		return false;
	}

	if(head != NULL){
		// traverse till the last node
		TaskNode* last;
		for(last = head; last->next != NULL; last = last->next);
		TaskNode* tmp = new TaskNode;
		tmp->task = task;
		tmp->next = NULL;
		last->next = tmp;
		return true;

	} else {
		head = new TaskNode;
		head->task = task;
		head->next = NULL;
		return true;
	}
}

bool removeTask(string taskName){
	if (head == NULL){
		return false;
	}

	if (taskName != ""){
		TaskNode* cur;
		TaskNode* prev;
		for(cur = head; cur->task->getTaskName() != taskName; cur = cur->next){
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

bool workGround::run(){
	bool successReport = true;
	bool enteredLoop   = false;
	if(head != NULL){
		for (TaskNode* cur = head; cur != NULL; cur = cur->next){
			successReport = successReport && cur->run();
			enteredLoop   = true;
		}
	}

	return successReport && enteredLoop;
}