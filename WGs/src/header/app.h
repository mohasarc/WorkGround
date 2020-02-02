#ifndef APP_H
#define APP_H

#include <iostream>
#include "WGList.h"
#include <fstream>
#include "..\external libraries\ezOptionParser.hpp"

using namespace ez;

template <typename T>
bool saveToFile(T data, string fileName, string ext);
bool readFile(string fileName, string ext, string& data);
//bool readFile(string fileName, string ext, WGList* data);
//bool saveObjToFile(WGList data, string fileName, string ext);
void Usage(ezOptionParser& opt);

#endif