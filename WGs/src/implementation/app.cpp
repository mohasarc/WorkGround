#include "..\header\app.h"

int main(int argc, const char* argv[]) {
	// variables
	ez::ezOptionParser opt;
	vector<vector<string>> strs;
	vector<string> parsedStrs;
	string wgNameTmp = "";
	string taskNameTmp = "";
	string fileNameTmp = "";
	string pathTmp = "";

	// add app info
	opt.overview = "WorkGround app.";
	opt.syntax = "complete first second [OPTIONS] in1 [... inN] out";
	opt.example = "complete a b -f --list 1,2,3 --list 4,5,6,7,8 -s string -int -2147483648,2147483647 -ulong 9223372036854775807 -float 3.40282e+038 -double 1.79769e+308 f1 f2 f3 f4 f5 f6 fout\n\n";
	opt.footer = "WorkGround 1.0.0  Copyright (C) 2020 \nThis program is free and without warranty licensed with MIT licese.\n";

	// create options
	opt.add(
		"", // Default.
		0, // Required?
		0, // Number of args expected.
		0, // Delimiter if expecting multiple args.
		"Display usage instructions.", // Help description.
		"-h",     // Flag token. 
		"-help",  // Flag token.
		"--help", // Flag token.
		"--usage" // Flag token.
	);

	opt.add(
		"", // Default.
		0, // Required?
		1, // Number of args expected.
		0, // Delimiter if expecting multiple args.
		"A pointer to a WorkGround or Task name.", // Help description.
		"pt" // Flag token.
	);

	opt.add(
		"", // Default.
		0, // Required?
		1, // Number of args expected.
		0, // Delimiter if expecting multiple args.
		"A pointer to a WorkGround or Task name.", // Help description.
		"view" // Flag token.
	);

	opt.add(
		"", // Default.
		0, // Required?
		0, // Number of args expected.
		0, // Delimiter if expecting multiple args.
		"To view elaborately.", // Help description.
		"-elab" // Flag token.
	);

	opt.add(
		"", // Default.
		3, // Required?
		4, // Number of args expected.
		',', // Delimiter if expecting multiple args.
		"to add tasks to WorkGrounds or files to tasks.", // Help description.
		"add" // Flag token.
	);

	opt.add(
		"", // Default.
		1, // Required?
		1, // Number of args expected.
		0, // Delimiter if expecting multiple args.
		"To run the specifired WorkGround.", // Help description.
		"run" // Flag token.
	);

	// parse the input
	opt.parse(argc, argv);

	// run option
	// Help Option
	if (opt.isSet("-h")) {
		cout << "in isset";
		//Usage(opt);
		return 1;
	}

	// pt Option
	opt.get("pt")->getMultiStrings(strs);
	if (opt.isSet("pt")) {
		for (unsigned i = 0; i < strs.size(); i++) {
			if (strs[i][0] != "") {
				 //save the name in the pointer
				saveToFile(strs[i][0], PT_FILE_NAME, EXT);
				cout << "pt = " << strs[i][0] << endl;
			}
		}

		// if only pt show its value
		if (strs.size() < 1) {
			string ptValue;
			readFile(PT_FILE_NAME, EXT, ptValue);
			cout << "pt = " << ptValue << endl;
		}
		
	}
	
	// View WorkGrounds Option
	opt.get("view")->getMultiStrings(strs);
	if (opt.isSet("-elab")) { // view elaborately
		if (opt.isSet("view")) {
			init(); // retrieving stored data
			if(strs.size() > 0 )
				for (int i = 0; i < strs[0].size(); i++) {
					if (strs[0][i] != "" && strs[0][i] != "pt") {
						string wgNameTmp = strs[0][i];
						cout << wgs.viewWgElab(wgNameTmp);
					}
					else if (strs[0][i] == "pt"){
						string wgNameTmp;
						readFile(PT_FILE_NAME, EXT, wgNameTmp);
						cout << wgs.viewWgElab(wgNameTmp);
					}
				}
		}
	}
	else { // view just wg names
		if (opt.isSet("view")) {
			init(); // retrieving stored data
			cout << wgs.viewWG();
		}
	}

	// Add option
	opt.get("add")->getMultiStrings(strs);
	if (opt.isSet("add")) {
		init(); // retrieving stored data
		if (strs.size() > 0) {
			parsedStrs = parseStrs(strs[0]);
			if (parsedStrs.size() >= 3) { // least number of args = 3
				wgNameTmp = parsedStrs[0];
				taskNameTmp = parsedStrs[1];
				parsedStrs.size() > 3 ? fileNameTmp = parsedStrs[2] : fileNameTmp = "";
				parsedStrs.size() > 3 ? pathTmp = parsedStrs[3] : pathTmp = parsedStrs[2];

				// Create the WorkGround if it doesn't exist
				wgs.addWg(wgNameTmp);

				// create and add task
				if (parsedStrs.size() == 3) {
					wgs.addTask(wgNameTmp, taskNameTmp, pathTmp);
					cout << "Task " << taskNameTmp << " was added" << endl;
				}
				else if (parsedStrs.size() == 4) { // create and add file
					wgs.addFile(wgNameTmp, taskNameTmp, fileNameTmp, pathTmp);
					cout << "File " << fileNameTmp << " was added" << endl;
				}
			}

		}
		store(); // store changes
	}

	// Run WorkGround Option
	opt.get("run")->getMultiStrings(strs);
	if (opt.isSet("run")) {
		init();
		if (strs.size() > 0) {
			parsedStrs = parseStrs(strs[0]);
			if (parsedStrs.size() > 0) {
				wgNameTmp = parsedStrs[0];
				bool success = wgs.runWG(wgNameTmp);
				if (success)
					cout << "The WorkGround \"" << wgNameTmp << "\" was run successfully";
				else
					cout << "Oops! there was a problem running the WorkGround \"" << wgNameTmp << "\"";
			}
		}
	}
	

	return 0;
}

template <typename T>
bool saveToFile(T data, string fileName, string ext){
	// make data directory
	_wmkdir(DATA_DIR.c_str());
	SetFileAttributes(DATA_DIR.c_str(), FILE_ATTRIBUTE_HIDDEN);

	// open out stream
	std::ofstream file(DATA_DIR_S + "\\"+ fileName + "." + ext);
	file << data;
	file.close();

	return true;
}

bool readFile(string fileName, string ext, string &data){
	ifstream inFile;
	inFile.open(DATA_DIR_S + "\\" + fileName + "." + ext);
	if (!inFile) {
		std::cerr << "error";
		return false;
	}
	
	data = "";
	string dataRead = "";
	while (inFile >> dataRead)
	{
		data += dataRead;
	}

	return true;
}

bool store() {
	// make data directory
	_wmkdir(DATA_DIR.c_str());
	SetFileAttributes(DATA_DIR.c_str(), FILE_ATTRIBUTE_HIDDEN);


	// open out stream
	std::ofstream file(DATA_DIR_S + DATA_FILE_NAME);
	file << wgs;
	file.close();

	return true;
}

bool init() {
	ifstream in(DATA_DIR_S + DATA_FILE_NAME);

	if (!in) {
		std::cerr << "error";
		return false;
	}
	in >> wgs;
	in.close();
	return true;
}

vector<string> parseStrs(vector<string> strs) {
	vector<string> result;
	if (strs.size() > 0) {
		for (int i = 0; i < strs.size(); i++) {
			if (strs[i] == "pt") {
				string ptValue;
				readFile(PT_FILE_NAME, EXT, ptValue);
				result.push_back(ptValue);
			}
			else {
				result.push_back(strs[i]);

			}
		}
	}
	return result;
}

void Usage(ezOptionParser& opt) {
	std::string usage;
	opt.getUsage(usage);
	std::cout << usage;
};