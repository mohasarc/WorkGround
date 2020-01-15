#ifndef APP_H
#define APP_H

#include <iostream>
#include <vector> 
#include "task.h"
#include "WorkGround.h"
using namespace std;

int main();
// void mainMenu();
// void VMWGMenu();
// void MWGMenu();
string viewWG(const vector<WorkGround*> wgs, bool elaborated);
string viewMenu(int which);
bool addWgTo(vector<WorkGround*> &wgs, string wgName, string taskName, string taskPath);
string askForWgName();
string askForWgName(string oldWgName);
string askForTaskName();
string askForTaskPath();
#endif