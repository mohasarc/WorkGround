#include "..\header\WGList.h"

WGList::WGList() {}

WGList::~WGList() {}

WGList::WGList(const WGList &toCopy) {
	for (unsigned i = 0; i < wgs.size(); i++)
		*wgs[i] = *toCopy.wgs[i];
}

void WGList::operator=(WGList& rhs) {
	for (unsigned i = 0; i < wgs.size(); i++)
		*wgs[i] = *rhs.wgs[i];
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
			if (i != 0 && i % itemPerLine == 0) // to print a number of items per line
				wgInfoTmp += "\n";
		}
	return wgInfoTmp;
}

string WGList::viewWgElab(string wgName) {
	bool found = false;
	string wgInfoTmp;
	// view WorkGrounds' details
	wgInfoTmp = string("\n--------------------------------------------------\n") +
						 "                  WORKGROUNDS LIST                \n" +
						 "--------------------------------------------------\n";
	if (wgs.size() <= 0)
		wgInfoTmp += "\nThere are no WorkGrounds yet to be viewed\n";
	else
		for (int i = 0; i < wgs.size() && !found; i++) {
			if (wgName == "*") { // view all
				wgInfoTmp += wgs[i]->wgView();

			} else if (wgs[i]->getWgName() == wgName) {
				wgInfoTmp += wgs[i]->wgView();
				found = true;
			}
		}
	if (!found && wgName != "*") {
		wgInfoTmp += "\n There is no WorkGround with the name : " + wgName + "\n";
	}
	return wgInfoTmp;
}

bool WGList::addWg(const string wgName) {
	WorkGround* tmpWg = findWg(wgName);

	if (wgName == "" | tmpWg != NULL)
		return false;
	else {
		WorkGround* newWG = new WorkGround(wgName);
		wgs.push_back(newWG);

		return true;
	}
}

bool WGList::removeWg(const string wgName) {
	WorkGround* tmpWg = findWg(wgName);

	for (unsigned i = 0; i < wgs.size(); i++) {
		if (wgs[i]->getWgName() == wgName) {
			wgs.erase(wgs.begin() + i);
			return true;
		}
	}

	return false;
}

bool WGList::renameWg(const string oldWgName, const string newWgName) {
	WorkGround* tmpWg = findWg(oldWgName);
	WorkGround* tmpWg2 = findWg(newWgName);

	if (tmpWg == NULL | tmpWg2 != NULL)
		return false;
	else {
		tmpWg->renameWorkGround(newWgName);
		return true;
	}
}

bool WGList::addTask(const string wgName, const string taskName, const string taskPath) {
	WorkGround* tmpWg = findWg(wgName);
	if (tmpWg == NULL)
		return false;
	else {
		Task task(taskName, taskPath);
		return tmpWg->addTask(task);
	}
}

bool WGList::removeTask(const string wgName, const string taskName) {
	WorkGround* tmpWg = findWg(wgName);
	if (tmpWg == NULL)
		return false;
	else {
		return tmpWg->removeTask(taskName);
	}
}

bool WGList::renameTask(const string wgName, const string oldTaskName, const string newTaskName) {
	WorkGround* tmpWg = findWg(wgName);
	if (tmpWg == NULL)
		return false;
	else {
		Task* taskPtr = tmpWg->findTask(oldTaskName);
		Task* taskPtr2 = tmpWg->findTask(newTaskName);
		if (taskPtr == NULL | taskPtr2 != NULL)
			return false;
		else {
			taskPtr->renameTask(newTaskName);
			return true;
		}
	}
}

bool WGList::addFile(const string wgName, const string taskName, const string fileName, const string filePath) {
	WorkGround* tmpWg = findWg(wgName);
	if (tmpWg == NULL)
		return false;
	else {
		Task* taskPtr;
		taskPtr = tmpWg->findTask(taskName);
		if (taskPtr != NULL) {
			return taskPtr->addFile(filePath, fileName);
		}
		return false;
	}
}

bool WGList::removeFile(const string wgName, const string taskName, const string fileName) {
	WorkGround* tmpWg = findWg(wgName);
	if (tmpWg == NULL)
		return false;
	else {
		Task* taskPtr;
		taskPtr = tmpWg->findTask(taskName);
		if (taskPtr != NULL) {
			return taskPtr->removeFile(fileName);
		}
		return false;
	}
}

bool WGList::renameFile(const string wgName, const string taskName, const string oldFilaName, const string newFileName) {
	WorkGround* tmpWg = findWg(wgName);
	if (tmpWg == NULL)
		return false;
	else {
		Task* taskPtr;
		taskPtr = tmpWg->findTask(taskName);
		if (taskPtr == NULL)
			return false;
		else {
			return taskPtr->renameFile(oldFilaName, newFileName);
		}
	}
}

bool WGList::runWG(const string wgName) {
	WorkGround* tmpWg = findWg(wgName);
	if (tmpWg == NULL)
		return false;
	else {
		return tmpWg->run();
	}
}

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
	WorkGround* tmpWg = findWg(wgName);
	Task* tmpTask;

	if (tmpWg == NULL) // if not found
		return NULL;
	else {
		tmpTask = tmpWg->findTask(taskName);
		return tmpTask;
	}
}

ostream& operator<<(ostream& out, const WGList& toSave) {
	out << toSave.wgs.size();

	for (int i = 0; i < toSave.wgs.size(); i++) {
		out << "\n" << *toSave.wgs[i];
	}
	out << endl;
	return out;
}

istream& operator>>(istream& in, WGList& retrieved) {
	int wgNo = 0;
	in >> wgNo;

	WorkGround* tmp;
	for (int i = 0; i < wgNo; i++) {
		tmp = new WorkGround();
		in >> *tmp;
		retrieved.wgs.push_back(tmp);
	}
	return in;
}