// ************************************************
// Functions to parse a sequence of ints and ranges
// ************************************************
// Author : Mohammed S. Yaseen
// Date	  :	22/03/2020

#include "..\header\sequenceParser.h"
#include <iostream>

bool parseRange(string sequence, map<int, int>& parsedsequence) {
	vector<string> partitions;
	partitions = partition(sequence, ',');
	int leftOfRange, rightOfRange;

	// for each partition
	for (string i : partitions) {
		// If number just add it
		if (isInt(i))
			parsedsequence.insert(pair<int, int>(stoi(i), 0));
		// If range add all in between inclusive
		else if (isRange(i, leftOfRange, rightOfRange)) {
			for (int j = leftOfRange; j <= rightOfRange; j++) {
				parsedsequence.insert(pair<int, int>(j, 0));
			}
		}
		// Not a valid character or Not a valid range 
		else {
			return false;
		}
		/// Using a map so no number is repeated
	}

	return true;
}

bool isRange(string range, int& leftNumber, int& rightNumber) {
	// there is not at least a number at the begining and at the end
	if (!isInt(range[0]) | !isInt(range[range.size() - 1]))
		return false;

	int hiphenExist = 0;
	string leftNum = "";
	string rightNum = "";

	for (char i : range) {
		// Niether a number nor a -
		if (!isInt(i) && i != '-')
			return false;
		// There is more than one -
		else if (i == '-' && hiphenExist != 0)
			return false;
		// The first - found
		else if (i == '-' && hiphenExist == 0)
			hiphenExist++;
		// Before - add to the left num
		else if (!hiphenExist)
			leftNum += i;
		// After - add to right num
		else if (hiphenExist)
			rightNum += i;
	}

	// If there is no -
	if (!hiphenExist)
		return false;

	// Left is larger than right -invalid range-
	if (stoi(leftNum) > stoi(rightNum))
		return false;

	leftNumber = stoi(leftNum);
	rightNumber = stoi(rightNum);
	return true;
}

bool isInt(string str) {
	if (str == "")
		return false;

	for (int i = 0; i < str.size(); i++) {
		if (str[i] < 48 | str[i] > 57)
			return false;
	}

	return true;
}

bool isInt(char chr) {
	if (chr < 48 | chr > 57)
		return false;

	return true;
}

vector<string> partition(string str, char delim) {
	vector<string> partitioned;
	string part = "";
	if (str == "")
		return partitioned;

	for (int i = 0; i < str.size(); i++) {
		if (str[i] != delim) {
			part += str[i];
		}
		if (str[i] == delim | i == str.size() - 1) {
			partitioned.push_back(part);
			part = "";
		}
	}

	return partitioned;
}