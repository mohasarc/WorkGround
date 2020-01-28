#ifndef APP_H
#define APP_H

#include <iostream>
#include <vector> 
#include "task.h"
#include "workGround.h"
using namespace std;

int main();
string viewWG(const vector<WorkGround*> wgs, bool elaborated);
string viewMenu(int which);
bool addWgTo(vector<WorkGround*> &wgs, string wgName, string taskName, string taskPath);
string askForName(int which);
string askForPath(int which);
string askForName(int which, string oldName);
string askForPath(int which, string oldPath);
#endif