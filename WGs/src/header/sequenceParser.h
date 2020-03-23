#ifndef SEQUENCEPARSER_H
#define SEQUENCEPARSER_H
#include <vector>
#include <string>
#include <map>
using namespace std;

// Functions
extern bool parseRange(string sequence, map<int, int>& parsedsequence);
extern bool isRange(string range, int& leftNumber, int& rightNumber);
extern bool isInt(string str);
extern bool isInt(char chr);
vector<string> partition(string str, char delim);
#endif