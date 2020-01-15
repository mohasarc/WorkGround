#include "app.h"

int main(){
	// variables
	vector<WorkGround*> workGrounds;
	char selection = '\n';
	WorkGround* newWG;
	Task* newTask;
	string wgName;
	string taskName;
	string taskPath;

	// the main program
	do{
		selection = '\n';
		// show the menu
		cout<< viewMenu(0);

		// getting the selection
		cin>>selection;

		// evaluate the selection
		switch(selection){
		case '1': 
			do {
				selection = '\n';

				// show the menu
				cout<< viewMenu(1);

				// getting selection
				cin>>selection;

				//************************//
				// Modify workground Menu //
				//************************//
				switch(selection){
				case 'a': // view WorkGrounds names
					cout<< viewWG(workGrounds, 0);
				break;

				case 'b': // view WorkGrounds content
					cout<< viewWG(workGrounds, 1);
				break;

				case 'c': // add a workground
					wgName = askForWgName();
					taskName = askForTaskName();
					taskPath = askForTaskPath();
					addWgTo(workGrounds, wgName, taskName, taskPath);
				break;

				case 'd':
					//************************//
					// Modify workground Menu //
					//************************//
					wgName = "";

					// view WorkGrounds' names
					cout<< viewWG(workGrounds, 0);

					cout<< "select the WorkGround to modify\n";
					wgName = askForWgName();

					// find the WorkGround
					for (int i = 0; i < workGrounds.size(); i++){
						if (workGrounds[i]->getWgName() == wgName)
							newWG = workGrounds[i];
					}

					if (!newWG){
						cout<<"There are no workgrounds just yet!\n";
				   		break;
					} else {
						do{
							selection = '\n';
							cout<<viewMenu(2);

							// getting selection
							cin>>selection;
							switch(selection){
							case 'a': //rename WorkGround
								wgName = askForWgName(newWG->getWgName());
								newWG->renameWorkGround(wgName);
							break;
	      					
							case 'b': //add a task
								taskName = askForTaskName();
								taskPath = askForTaskPath();
								// create task and add it to workground
								newTask = new Task(taskName, taskPath);
								newWG->addTask(*newTask);
							break;

							case 'c': //remove a task
								// view the workground tasks
								cout<<newWG->wgView()<<endl;
								cout<<"select the task to remove\n";
								taskName = askForTaskName();

								// remove the task with the name taskName
								newWG->removeTask(taskName);
							break;

							// case 'd': //modify a task
								// 	// view the workground tasks
								// 	cout<<newWG->wgView()<<endl;
								// 	cout<<"select the task to modify\ntype its name : ";
								// 	getline(cin, taskName);

								// 	// get the task with the name taskName to modify it

							// break;
							}
						}while(selection != 'r' && selection != 'R');
					}

					selection = '\n';
					break;
				}
			} while (selection != 'r' && selection != 'R');
		break;

		// case '2': 


		// break;

		// case '3': 


		// break;

		// case '4': 


		// break;

		// case '5': 


		// break;

		// case '6': 


		// break;
		}
	} while (selection != 'q' && selection != 'Q');
}

string viewMenu(int which){
	string theMenu = "";
	switch(which){
		case 0:
			theMenu = string("Please select a choice (choose 1, 2, .. etc)\n") +
		    		"1- View and Mpdify WorkGrounds\n" +
		    		"2- Switch current WorkGround\n" +
		    		"3- Choose a default WorkGround\n" +
		    		"4- start automatically after booting up\n" +
		    		"5- other settings\n" +
		    		"6- about\n" +
		    		"Q- Quit\n";

		    return theMenu;
		break;

		case 1:
			theMenu = string("Please select a choice (choose a, b, .. etc)\n") +
					"a- View WorkGrounds (siplified)\n" +
					"b- View WorkGrounds (elaborated)\n" +
					"c- Add a WorkGround\n" +
					"d- Modify a WorkGround\n" +
					"e- Remove a WorkGround\n" +
					"r- Return to previous menu\n";

			return theMenu;
		break;

		case 2:
			theMenu = string("select one\n") +
					"a - rename WorkGround\n" +
					"b - add a task\n" +
					"c - remove a task\n" +
					"d - modify a task\n" +
					"r - return to the previous menu\n";

			return theMenu;
		break;

		default:
			return "";
		break;
	}
}

string viewWG(const vector<WorkGround*> wgs, bool elaborated){
	string wgInfoTmp;

	if (!elaborated){
		// view WorkGrounds' names
		wgInfoTmp = "";

		if (wgs.size() <= 0)
			return "there are no WorkGrounds yet to be viewed\n";

		for (int i = 0; i < wgs.size(); i++){
			wgInfoTmp += wgs[i]->getWgName() + "\t";
		
			if( i % 4 == 0)
				wgInfoTmp += "\n";
		}
		return wgInfoTmp;

	} else { 
		// view WorkGrounds' details
		wgInfoTmp = "";

		if (wgs.size() <= 0)
			return "there are no WorkGrounds yet to be viewed\n";

		for (int i = 0; i < wgs.size(); i++)
			wgInfoTmp += wgs[i]->wgView();
		return wgInfoTmp;
	}
}

bool addWgTo(vector<WorkGround*> &wgs, string wgName, string taskName, string taskPath){
	WorkGround* newWG = new WorkGround(wgName);
	Task* newTask = new Task(taskName, taskPath);

	newWG->addTask(*newTask);

	wgs.push_back(newWG);
}

string askForWgName(){
	string wgName = "";

	cout<< "specify the workground name : ";
	cin.ignore();
	getline(cin, wgName);
	cout<<"\n";

	return wgName;
}

string askForWgName(string oldWgName){
	string wgName = "";
	cout<< "Old name: " + oldWgName + "\n";
	return askForWgName();
}

string askForTaskName(){
	string taskName = "";
	cout<< "choose a task Name : ";
	cin.ignore();
	getline(cin, taskName);
	cout<<"\n";

	return taskName;
}
string askForTaskPath(){
	string taskPath = "";
	cout<< "add the program path (in the form C:\\Program file\\....)\nThe path:";
	cin.ignore();
	getline(cin, taskPath);

	return taskPath;
}