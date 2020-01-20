#include "..\header\WGList.h"

WGList::WGList(WGList &toCopy) {
	for (unsigned i = 0; i < wgs.size(); i++)
		wgs[i] * = toCopy.wgs[i] *;
}

WGList::operator=(WGList& rhs) {
	for (unsigned i = 0; i < wgs.size(); i++)
		wgs[i] * = rhs.wgs[i] *;
}

string WGList::viewWG() {
	string wgInfoTmp;
	unsigned itemPerLine = 4;
	// view WorkGrounds' names
	wgInfoTmp = string("\n--------------------------------------------------\n") +
						 "                  WORKGROUNDS LIST                \n" +
						 "--------------------------------------------------\n";
	if (wgs.size() <= 0)
		wgInfoTmp += "\nThere are no WorkGrounds yet to be viewed\n";
	else
		for (int i = 0; i < wgs.size(); i++) {
			wgInfoTmp += wgs[i]->getWgName() + "\t";
			if (i % itemPerLine == 0) // to print a number of items per line
				wgInfoTmp += "\n";
		}
	return wgInfoTmp;
}

string WGList::viewWgElab() {
	string wgInfoTmp;
	// view WorkGrounds' details
	wgInfoTmp = string("\n--------------------------------------------------\n") +
						 "                  WORKGROUNDS LIST                \n" +
						 "--------------------------------------------------\n";
	if (wgs.size() <= 0)
		wgInfoTmp += "\nThere are no WorkGrounds yet to be viewed\n";
	else
		for (int i = 0; i < wgs.size(); i++)
			wgInfoTmp += wgs[i]->wgView();
	return wgInfoTmp;
}

bool WGList::addWg(const string wgName) {
	WorkGround* tmpWg = findWg(wgs, wgName);

	if (wgName == "" | tmpWg != NULL)
		return false;
	else {
		WorkGround* newWG = new WorkGround(wgName);
		wgs.push_back(newWG);

		return true;
	}
}

bool WGList::removeWg(const string wgName) {
	WorkGround* tmpWg = findWg(wgs, wgName);

	for (unsigned i = 0; i < wgs.size(); i++) {
		if (wgs[i]->getWgName() == wgName) {
			wgs.erase(wgs.begin() + i);
			return true;
		}
	}

	return false;
}

bool WGList::renameWg(const string oldWgName, const string newWgName) {
	WorkGround* tmpWg = findWg(wgs, oldWgName);
	if (tmpWg == NULL)
		return false;
	else {
		tmpWg->renameWorkGround(newWgName);
		return true;
	}
}

bool WGList::addTask(const string wgName, const string taskName, const string taskPath) {
	WorkGround* tmpWg = findWg(wgs, wgName);
	if (tmpWg == NULL)
		return false;
	else {
		Task task(taskName, taskPath);
		tmpWg->addTask(task);
		return true;
	}
}

bool WGList::removeTask(const string wgName, const string taskName) {
	WorkGround* tmpWg = findWg(wgs, wgName);
	if (tmpWg == NULL)
		return false;
	else {
		return tmpWg->removeTask(taskName);
	}
}

bool WGList::renameTask(const string wgName, const string oldTaskName, const string newTaskName) {
	WorkGround* tmpWg = findWg(wgs, wgName);
	if (tmpWg == NULL)
		return false;
	else {
		Task* taskPtr;
		taskPtr = tmpWg->findTask(oldTaskName);
		if (taskPtr != NULL) {
			taskPtr->renameTask(newTaskName);
			return true;
		}
		return false;
	}
}

bool WGList::addFile(const string wgName, const string taskName, const string filaName, const string filePath) {
	WorkGround* tmpWg = findWg(wgs, wgName);
	if (tmpWg == NULL)
		return false;
	else {
		Task* taskPtr;
		taskPtr = tmpWg->findTask(oldTaskName);
		if (taskPtr != NULL) {
			taskPtr->renameTask(newTaskName);
			return true;
		}
		return false;
	}
}

bool WGList::removeFile(Task& task, const string filaName);

bool WGList::renameFile(Task& task, const string oldFilaName, const string newFileName);

WorkGround* WGList::findWg(string wgName) {
	WorkGround* tmpWG;
	for (unsigned i = 0; i < wgs.size(); i++) {
		if (wgs[i]->getWgName() == wgName) {
			tmpWG = wgs[i];
			return tmpWG;
		}
	}
	// if not found
	return NULL;
}

Task* WGList::findTask(string wgName, string taskName) {
	WorkGround* tmpWg = findWg(wgs, wgName);
	Task* tmpTask;

	if (tmpWg == NULL) // if not found
		return NULL;
	else {
		tmpTask = tmpWg->findTask(taskName);
		return tmpTask;
	}
}