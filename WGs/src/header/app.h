#ifndef APP_H
#define APP_H

#include <iostream>
#include "..\external libraries\ezOptionParser.hpp"
#include "WGList.h"
using namespace ez;

template <typename T>
bool saveToFile(T data, string fileName, string ext);
bool readFile(string fileName, string ext, string& data);
bool store();
bool init();
vector<string> parseStrs(vector<string> strs);
void Usage(ezOptionParser& opt);

// Global Variables
WGList wgs;

// constantss
const string DATA_DIR_S = ".\\.data";
const wstring DATA_DIR = L".\\.data";
const string DATA_FILE_NAME = "\\data.wg";
const string PT_FILE_NAME = "pt";
const string EXT = "wg";
#endif