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
		cout<< "Please select a choice (choose 1, 2, .. etc)\n" <<
		       "1- View and Mpdify WorkGrounds\n" <<
		       "2- Switch current WorkGround\n" <<
		       "3- Choose a default WorkGround\n" <<
		       "4- start automatically after booting up\n" <<
		       "5- other settings\n" <<
		       "6- about\n"<<
		       "Q- Quit\n";

		// getting the selection
		cin>>selection;

		// evaluate the selection
		switch(selection){
			case '1': 
				do {
					selection = '\n';

					// show the menu
					cout<< "Please select a choice (choose a, b, .. etc)\n" <<
					       "a- View WorkGrounds (siplified)\n" <<
					       "b- View WorkGrounds (elaborated)\n" <<
					       "c- Add a WorkGround\n" <<
					       "d- Modify a WorkGround\n" <<
					       "e- Remove a WorkGround\n" <<
					       "r- Return to previous menu\n";

					// getting selection
					cin>>selection;
					       switch(selection){
					       		case 'a':
					       			// view WorkGrounds names
									for (int i = 0; i < workGrounds.size(); i++){
										cout<<workGrounds[i]->getWgName()<<"\t";
									
										if( i % 4 == 0)
											cout<<endl;
									}

									cout<<endl;
									if (workGrounds.size() == 0)
								  		cout<<"there are no WorkGrounds yet to be viewed\n";
					       		break;

					       		case 'b':
					       			// view WorkGrounds content
					       			for (int i = 0; i < workGrounds.size(); i++){
					       				cout<<workGrounds[i]->wgView();
					       			}

					       			if (workGrounds.size() == 0)
					       				cout<<"there are no WorkGrounds yet to be viewed\n";
					       		break;

					       		case 'c':

					       			// initalizing vars
					       			newWG = new WorkGround();
					       			wgName = "";
					       			taskName = "";
					       			taskPath = "";

					       			// getting input
					       			cout<< "specify a name : ";
					       			cin.ignore();
					       			getline(cin, wgName);
					       			cout<< "\nadd a task:\nchoose a task Name : ";
					       			// cin.ignore();
					       			getline(cin, taskName);
					       			cout<< "\nadd the program path (in the form C:\\Program file\\....)\n";
					       			cin.ignore();
					       			getline(cin, taskPath);
					       			
					       			// making objects
					       			newWG->renameWorkGround(wgName);
					       			newTask = new Task(taskName, taskPath);
					       			newWG->addTask(*newTask);

					       			// add to vector
					       			workGrounds.push_back(newWG);
					       		break;

					       		case 'd':
					       			// initializing vars
					       			wgName = "";

					       			// view WorkGrounds names
					       			cout<<"\nAvailable workGrounds' names :\n";
					       			for (int i = 0; i < workGrounds.size(); i++){
										cout<<workGrounds[i]->getWgName()<<"\t";
									
										if( i % 4 == 0)
											cout<<endl;
									}

									cout<<endl;
									if (workGrounds.size() == 0)
								  		cout<<"there are no WorkGrounds yet to be viewed\n";

					       			cout<< "select the WorkGround to modify\ntype its name : ";
					       			cin.ignore();
					       			getline(cin, wgName);

					       			// find the WorkGround
					       			for (int i = 0; i < workGrounds.size(); i++){
					       				if (workGrounds[i]->getWgName() == wgName){
					       					newWG = workGrounds[i];
					       				}
					       			}

					       			do{
					       				selection = '\n';
					       				// view the menu
					       				cout<<"select one\n"
					       					<<"a - rename WorkGround\n"
					       					<<"b - add a task\n" 
					       					<<"c - remove a task\n" 
					       					<<"d - modify a task\n"
					       					<<"r - return to the previous menu\n";

					       				// getting selection
					       				cin>>selection;

					       				// evaluating selection
					       				switch(selection){
					       					//rename WorkGround
					       					case 'a':
					       						cout<< "choose a new name for the workGround ( " 
					       							<< newWG->getWgName() << " ) : \n";
					       						cin.ignore();
					       						getline(cin, wgName);
					       						newWG->renameWorkGround(wgName);
					       					break;

					       					//add a task
					       					case 'b':
					       						// create the task
					       					cout<< "\nadd a task:\nchoose a task Name : ";
					       					cin.ignore();
					       					getline(cin, taskName);
					       					cout<< "\nadd the program path (in the form C:\\Program file\\....)\n";
					       					cin.ignore();
					       					getline(cin, taskPath);

					       						// add it to the workground
					       					newTask = new Task(taskName, taskPath);
					       					newWG->addTask(*newTask);

					       					break;

					       					//remove a task
					       					case 'c':
					       						// view the workground tasks
					       						cout<<newWG->wgView()<<endl;
					       						cout<<"select the task to remove\ntype its name : ";
					       						cin.ignore();
					       						getline(cin, taskName);

					       						// remove the task with the name taskName
					       						newWG->removeTask(taskName);
					       					break;

					       					//modify a task
					       					// case 'd':
					       					// 	// view the workground tasks
					       					// 	cout<<newWG->wgView()<<endl;
					       					// 	cout<<"select the task to modify\ntype its name : ";
					       					// 	getline(cin, taskName);

					       					// 	// get the task with the name taskName to modify it

					       					// break;
					       				}
					       			}while(selection != 'r' && selection != 'R');

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


// void viewWG(){
// 	// view WorkGrounds names
// 	for (int i = 0; i < workGrounds.size(); i++){
// 		cout<<workGrounds[i]->getWgName()<<"\t";
	
// 		if( i % 4 == 0)
// 			out<<endl;
// 	}

// 	cout<<endl;
// 	if (workGrounds.size() == 0)
//   		cout<<"there are no WorkGrounds yet to be viewed\n";
// }