#include "..\header\app.h"

int main(int argc, const char* argv[]) {
	// variables
	WGList* wgs = new WGList();
	WGList* wgs2 = new WGList();
	ez::ezOptionParser opt;
	vector<vector<string>> strs;

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
		1, // Required?
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

	// parse the input
	opt.parse(argc, argv);


	// run option
	if (opt.isSet("-h")) {
		cout << "in isset";
		//Usage(opt);
		return 1;
	}

	opt.get("pt")->getMultiStrings(strs);
	if (opt.isSet("pt")) {
		for (int i = 0; i < strs.size(); i++) {
			if (strs[i][0] != "") {
				// save the name in the pointer
				saveToFile(strs[i][0], "pt", "wgtmp");
				cout << "pt = " << strs[i][0] << endl;
			}
		}

		// if only pt show its value
		if (strs.size() < 1) {
			string ptValue;
			readFile("pt", "wgtmp", ptValue);
			cout << "pt = " << ptValue << endl;
		}
		
	}
	
	// view workgrounds
	opt.get("view")->getMultiStrings(strs);
	if (opt.isSet("-elab")) { // view elaborately
		if (opt.isSet("view")) {
			for (int i = 0; i < strs.size(); i++) {
				if (strs[i][0] == "pt") {
					string name;
					readFile("pt", "wgtmp", name);
					cout << "viewing " + name + " elaboratily";
				}
				else {
					cout << "viewing " + strs[i][0] + " elaboratily";
				}
			}
		}
	}
	else { // view just wg names
		if (opt.isSet("view")) {
			for (int i = 0; i < strs.size(); i++) {
				cout << "viewing " + strs[i][0];
			}
		}
	}
	
	//wgs->addWg("My wg");
	//saveObjToFile(*wgs, "workGrounds", "wgs");
	//readFile("workGrounds" , "wgs", wgs2);
	//cout << "file read";
	//cout<<wgs2->viewWG();
	//cout << "viewd";

	return 0;
}

template <typename T>
bool saveToFile(T data, string fileName, string ext){
	std::ofstream file;

	file.open("." + fileName + "." + ext);

	file << data;
	file.close();

	return true;
}

//bool saveObjToFile(WGList data, string fileName, string ext){
//	std::ofstream file;
//	file.open("." + fileName + "." + ext, ios::out);
//
//	if (!file) {
//		// error creating file
//		return false;
//	}
//	else {
//		file.write((char*)&data, sizeof(data));
//		file.close();
//	}
//}

bool readFile(string fileName, string ext, string &data){
	ifstream inFile;
	inFile.open(".\\." + fileName + "." + ext);
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

//bool readFile(string fileName, string ext, WGList* data) {
//	cout << "reading file";
//	ifstream file;
//	string theFileName = "." + fileName + "." + ext;
//	file.open(theFileName, ios::in);
//	if (!file) {
//		// error in opening file
//		return false;
//	}
//	else {
//		WGList tmpwg;
//		cout << "reading the file" << endl;
//		cout << "size of object" << sizeof(tmpwg) << endl;
//		file.read((char*)&tmpwg, sizeof(tmpwg));
//		cout << "file read"<<endl;
//		cout << "size of object" << sizeof(tmpwg) << endl;
//		file.close();
//	}
//}

void Usage(ezOptionParser& opt) {
	std::string usage;
	opt.getUsage(usage);
	std::cout << usage;
};