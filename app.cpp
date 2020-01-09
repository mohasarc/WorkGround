#include "app.h"

int main(){
	// vars
	vector<WorkGround*> workGrounds;
	char selection = '\n';


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

					       			// variables
					       			WorkGround* newWG = new WorkGround();
					       			Task* newTask;
					       			string wgName = "";
					       			string taskName = "";
					       			string taskPath = "";

					       			// getting input
					       			cout<< "specify a name : ";
					       			getline(cin, wgName);
					       			getline(cin, wgName);
					       			cout<< "\nadd a task:\nchoose a task Name : ";
					       			getline(cin, taskName);
					       			cout<< "\nadd the program path (in the form C:\\Program file\\....)\n";
					       			getline(cin, taskPath);
					       			
					       			// making objects
					       			newWG->renameWorkGround(wgName);
					       			newTask = new Task(taskName, taskPath);
					       			newWG->addTask(*newTask);

					       			// add to vector
					       			workGrounds.push_back(newWG);
					       		break;

					       		// case 'd':

					       		// break;
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