#include "..\header\app.h"

int main(){
	// variables
	WGList* wgs = new WGList();
	wgs->addWg("wg1");
	wgs->addWg("wg2");
	wgs->addWg("wg3");
	wgs->addWg("wg4");
	wgs->addWg("wg5");
	wgs->addWg("wg6");
	wgs->addWg("wg7");
	wgs->addWg("wg8");
	wgs->addWg("wg9");
	wgs->addWg("wg10");
	wgs->addWg("wg11");
	wgs->addWg("wg12");
	wgs->addWg("wg13");
	wgs->addWg("wg14");

	wgs->addTask("wg1", "t1", "\"C:\\Program Files (x86)\\Adobe\\Acrobat Reader DC\\Reader\\AcroRd32.exe\"");
	wgs->renameWg("wg1", "wg2");
	cout<<wgs->viewWG();
	cout<<wgs->viewWgElab();
	wgs->runWG("wg1");


	//Task t1;

	//vector<WorkGround*> workGrounds;
	//char selection = '\n';
	////WorkGround* tmpWG = NULL;
	////Task* tmpTask = NULL;
	//string wgNameStr;
	//string taskNameStr;
	//string fileNameStr;
	//string pathStr;
	//bool successOper;

	// the main program
	//do{
	//	selection = '\n';
	//	cout<< viewMenu(0);

	//	cin.get(selection);
	//	cin.ignore(256, '\n');

	//	switch(selection){
	//	case '1': 
	//		do {
	//			selection = '\n';
	//			cout<< viewMenu(1);

	//			cin.get(selection);
	//			cin.ignore(256, '\n');

	//			//************************//
	//			// Modify workground Menu //
	//			//************************//
	//			switch(selection){
	//			case 'a': // view WorkGrounds names
	//				cout<< wgs.viewWG();
	//			break;

	//			case 'b': // view WorkGrounds content
	//				cout<< wgs.viewWgElab();
	//			break;

	//			case 'c': // add a workground
	//				wgNameStr = askForName(0);

	//				wgs.addWg(wgNameStr);
	//			break;

	//			case 'd':
	//				//************************//
	//				// Modify workground Menu //
	//				//************************//
	//				wgNameStr = "";

	//				// view WorkGrounds' names
	//				cout<< viewWG(workGrounds, 0);

	//				cout<< "select the WorkGround to modify\n";
	//				wgNameStr = askForName(0);

	//				// find the WorkGround
	//				for (int i = 0; i < workGrounds.size(); i++){
	//					if (workGrounds[i]->getWgName() == wgNameStr)
	//						tmpWG = workGrounds[i];
	//				}

	//				if (!tmpWG){
	//					cout<<"There are no workgrounds just yet!\n";
	//			   		break;
	//				} else {
	//					do{
	//						selection = '\n';
	//						cout<<viewMenu(2);

	//						// getting selection
	//						cin.get(selection);
	//						cin.ignore(256, '\n');
	//						switch(selection){
	//						case 'a': //rename WorkGround
	//							wgNameStr = askForName(0, tmpWG->getWgName());
	//							tmpWG->renameWorkGround(wgNameStr);
	//						break;
	//      					
	//						case 'b': //add a task
	//							taskNameStr = askForName(1);
	//							pathStr = askForPath(0);
	//							// create task and add it to workground
	//							tmpTask = new Task(taskNameStr, pathStr);
	//							tmpWG->addTask(*tmpTask);
	//						break;

	//						case 'c': //remove a task
	//							// view the workground tasks
	//							cout<<tmpWG->wgView()<<endl;
	//							cout<<"select the task to remove\n";
	//							taskNameStr = askForName(1);

	//							// remove the task with the name taskNameStr
	//							tmpWG->removeTask(taskNameStr);
	//						break;

	//						case 'd': //modify a task
	//								cout<<tmpWG->wgView()<<endl;
	//								cout<<"select the task to modify\ntype its name : ";
	//								// get the task with the name taskNameStr to modify it
	//								taskNameStr = askForName(1);
	//								successOper = tmpWG->getTask(taskNameStr, tmpTask);

	//								if(!successOper)
	//									break;

	//								do {
	//									selection = '\n';
	//									cout<<viewMenu(3);

	//									// getting selection
	//									cin.get(selection);
	//									cin.ignore(256, '\n');
	//									switch(selection){
	//									case 'a': // rename a task
	//										taskNameStr = askForName(1, tmpTask->getTaskName());
	//										tmpTask->renameTask(taskNameStr);
	//									break;

	//									case 'b': // add a file
	//										pathStr = askForPath(1);
	//										fileNameStr = askForName(2);
	//										tmpTask->addFile(pathStr, fileNameStr);
	//									break;

	//									case 'c': // remove a file
	//										fileNameStr = askForName(2);
	//										successOper = tmpTask->removeFile(fileNameStr);
	//										cout<<successOper;
	//									break;

	//									case 'd':
	//										pathStr = askForPath(0, tmpTask->getAppPath());
	//										tmpTask->changeApp(pathStr);
	//									break;
	//									}
	//								}while(selection != 'r' && selection != 'R');
	//						break;
	//						}
	//					}while(selection != 'r' && selection != 'R');
	//				}

	//				selection = '\n';
	//				break;
	//			}
	//		} while (selection != 'r' && selection != 'R');
	//	break;

	//	case '2': //Start a workground
	//		cout<< viewWG(workGrounds, 0);
	//		wgNameStr = askForName(0);

	//		// find the workground obj
	//		tmpWG = NULL;
	//		for(int i = 0; i < workGrounds.size(); i++){
	//			if(workGrounds[i]->getWgName() == wgNameStr)
	//				tmpWG = workGrounds[i];
	//		}

	//		if(tmpWG)
	//			tmpWG->run();
	//	break;

	//	// case '3': 


	//	// break;

	//	// case '4': 


	//	// break;

	//	// case '5': 


	//	// break;

	//	// case '6': 


	//	// break;
	//	}
	//} while (selection != 'q' && selection != 'Q');
}

//string viewMenu(int which){
//	string theMenu = "";
//	switch(which){
//		case 0:
//			theMenu = string("\n--------------------------------------------------\n") +
//							   "                  THE MAIN MENU                   \n" +
//							   "--------------------------------------------------\n" +
//		    				   "|| 1- View and Mpdify WorkGrounds               ||\n" +
//		    				   "|| 2- Start a workground                        ||\n" +
//		    				   "|| 3- Choose a default WorkGround               ||\n" +
//		    				   "|| 4- start automatically after booting up      ||\n" +
//		    				   "|| 5- other settings                            ||\n" +
//		    				   "|| 6- about                                     ||\n" +
//		    				   "|| Q- Quit                                      ||\n" +
//		    				   "--------------------------------------------------\n" +
//		    				   "Please select a choice (choose 1, 2, .. etc) : ";
//
//		    return theMenu;
//		break;
//
//		case 1:
//			theMenu = string("\n--------------------------------------------------\n") +
//							   "           VIEW AND MODIFY WORKGROUNDS            \n" +
//							   "--------------------------------------------------\n" +
//							   "|| a- View WorkGrounds (siplified)              ||\n" +
//							   "|| b- View WorkGrounds (elaborated)             ||\n" +
//							   "|| c- Add a WorkGround                          ||\n" +
//							   "|| d- Modify a WorkGround                       ||\n" +
//							   "|| e- Remove a WorkGround                       ||\n" +
//							   "|| r- Return to previous menu                   ||\n" + 
//							   "--------------------------------------------------\n" +
//							   "Please select a choice (choose a, b, .. etc) : ";
//
//			return theMenu;
//		break;
//
//		case 2:
//			theMenu = string("\n--------------------------------------------------\n") +
//							   "                 MODIFY A WORKGROUND              \n" +
//							   "--------------------------------------------------\n" +
//							   "|| a - rename WorkGround                        ||\n" +
//							   "|| b - add a task                               ||\n" +
//							   "|| c - remove a task                            ||\n" +
//							   "|| d - modify a task                            ||\n" +
//							   "|| r - return to the previous menu              ||\n" + 
//							   "--------------------------------------------------\n" +
//							   "Please select a choice (choose a, b, .. etc) : ";
//
//			return theMenu;
//		break;
//
//		case 3:
//			theMenu = string("\n--------------------------------------------------\n") +
//							   "                    MODIFY A TASK                 \n" +
//							   "--------------------------------------------------\n" +
//							   "|| a - rename task                              ||\n" +
//							   "|| b - add a file                               ||\n" +
//							   "|| c - remove a file                            ||\n" +
//							   "|| d - change app path                          ||\n" +
//							   "|| r - return to the previous menu              ||\n" + 
//							   "--------------------------------------------------\n" +
//							   "Please select a choice (choose a, b, .. etc) : ";
//
//			return theMenu;
//		break;
//
//		default:
//			return "";
//		break;
//	}
//}
//
//bool addWgTo(vector<WorkGround*> &wgs, string wgName, string taskName, string taskPath){
//	WorkGround* newWG = new WorkGround(wgName);
//	Task* newTask = new Task(taskName, taskPath);
//
//	newWG->addTask(*newTask);
//
//	wgs.push_back(newWG);
//
//	return true;
//}
//
//string askForName(int which){
//	string name = "";
//
//	switch(which){
//		case 0: cout<< "specify the workground name : "; break;
//		case 1: cout<< "choose a task Name : "; break;
//		case 2: cout<< "choose a file nick name : "; break;
//	}
//	
//	getline(cin, name);
//	cout<<"\n";
//	return name;
//}
//
//string askForName(int which, string oldName){
//	cout<< "Old name: " + oldName + "\n";
//	return askForName(which);
//}
//
//string askForPath(int which){
//	string path = "";
//
//	switch(which){
//		case 0: cout<< "add a task path (in the form C:\\Program file\\....)\nThe path:"; break;
//		case 1: cout<< "add a file path (in the form C:\\Program file\\....)\nThe path:"; break;
//	}
//	
//	getline(cin, path);
//
//	// parsing the path
//	path.insert(0, 1,'\"');
//	path.insert(path.end(), 1,'\"');
//	for (int i = 0; i < path.length(); i++){
//		if(path[i] == '\\'){
//			path.insert((i), 1, '\\');
//			i++;
//		}
//	}
//
//	return path;
//}
//
//string askForPath(int which, string oldPath){
//	cout<< "Old path: " + oldPath + "\n";
//	return askForPath(which);
//}