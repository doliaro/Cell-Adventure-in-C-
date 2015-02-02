
#include "adventure.hpp"

string Room::getName(){
		return name;
	}

string Room::getDescription(){
	return description;
}

Room::Room(string n, string d){
	name = n;
	description = d;
}

void Room::assign(Room* &current_room, Room* north, Room* east, Room* south, Room* west){

	current_room->northLink = north;
	current_room->eastLink = east;
	current_room->southLink = south;
	current_room->westLink = west;
}

void animate(){
	std::cout << '-' << std::flush;
    for (;;) {
        system("sleep .18");
        std::cout << "\b\\" << std::flush;
        system("sleep .18");
        std::cout << "\b|" << std::flush;
        system("sleep .18");
        std::cout << "\b/" << std::flush;
        system("sleep .18");
        std::cout << "\b-" << std::flush;
        break;
    }
}

//MOVE PLAYER
void move(string direction, Room* &current, Room* &temp){

bool out = false;
	while(out == false){
		if(direction == "n"){
			current = current->northLink;
			out = true;
		}
		if(direction == "e"){
			current = current->eastLink;
			out = true;
		}
		if(direction == "s"){
			current = current->southLink;
			out = true;
		}
		if(direction == "w"){
			current = current->westLink;
			out = true;
		}
		if(current == NULL){
			cout << "No path that way. Check your map!" << endl;
			break;
		}

		animate();
		//this just stores this name into a separate variable so it can be printed in all caps
		string name = current->getName();
		std::transform(name.begin(), name.end(), name.begin(), toupper);
		cout << "                ---------------------- " << name << " ----------------------" << endl;
		cout <<"       "<< current->getDescription() << endl << endl;

		temp = current;
		//FIGURE OUT HOW TO GET OUT
	}		
}

//NAVIGATION
void navigation(string &path, Room* &current, Room* &temp){
	bool out = false;
	while(out == false && path != "x"){

		if(path == "n"){
			move("n", current, temp);
			out = true;
		}	
	
		if(path == "e"){
			move("e", current, temp);
			out = true;
		}	
		if(path == "s"){
			move("s", current, temp);
			out = true;
		}	
		//Into lysosome
		if(path == "w"){
			move("w", current, temp);
			out = true;
		}	
		if(current == NULL)
			out = false;
			break;
	}		
}

void checkInput(string &input){
	bool input_good = false;

	while(input_good == false){	
		if ((input != "x") && (input != "m") && (input != "n") && (input != "e") &&
		    (input != "s") && (input != "w") && (input != "b") && (input != "y") && 
		    (input != "h") && (input != "l") && (input != "1") && (input != "2") && 
		    (input != "3") && (input != "f"))
		{
			cout << "Command not recognized - Try again: ";
			getline(cin, input);
			std::transform(input.begin(), input.end(), input.begin(), ::tolower);
			checkInput(input);
		}
		else {
			input_good = true;
			break;
		}	
	}	
}

void checkEnergy(int energy_level){
	cout << "                      [Current Energy Level] "<< endl;
	cout << "                                                                                   " << energy_level << endl;
	if (energy_level == 3){  
		cout << "            !!!! Your energy levels are getting low. Find some energy !!!!" << endl;
	}
	if (energy_level == 1){
		cout << "     !!!!!!!! Your energy levels are critically low. You need energy immediately. !!!!!!!!" << endl;
	}
	if (energy_level < 0) {
		cout << "                 !!!!!!!!!!!!!!!!!!!! GAME OVER !!!!!!!!!!!!!!!!!!!!" << endl; 
		cout << "                  You are out of energy, and can no longer navigate " << endl << endl;
		cout << "                 ~~Get comfortable here, this cell is your new home~~" << endl;
		exit(0);
	}
}

void specialRoomCheck(Room* current, Mitochondria &mit, Room* mitochondria, Room* cytoplasm, Room* nucleus, Room* &ribosome, Room* &membrane, Room* outside){
	if (current == mitochondria){
		cout << current->displayMessage();
	}	
	if (current == ribosome ){
		cout << current->displayMessage();
	}
	if (current == nucleus){
		cout << current->displayMessage();
	}
	if (current == membrane){
		int mit_protein = mit.getProtein();
		if (mit_protein == 1){
			cout << "                            !!! Escape the cell by going north !!!\n\n";
			membrane->assign(membrane, outside, NULL, cytoplasm, NULL);
		}	
	}
}

void shootLaser(Room* current, Room* &ribosome, Room* &nucleus){
	string item_to_check = current->displayItem();
	string confirm;

	if(item_to_check == ""){
		cout << "Dont do that! This organelle is fragile" << endl;
	}
	else {
		cout << "There is " << item_to_check << " in this organelle. Are you sure you want to destroy it? (y/n) ";
		getline(cin, confirm);
		std::transform(confirm.begin(), confirm.end(), confirm.begin(), ::tolower);
		if (confirm != "y" && confirm != "n"){
			cout << "Invalid input" << endl;
		}
		if (confirm == "y"){
			cout << "                     ~~~~~You have destroyed the " << current->displayItem() << "~~~~~" << endl;
			current->setItem("");
			current->displayMessage();
			if (item_to_check == "Foreign Matter"){
				nucleus->setMessage( "                   ** The nucleus appears to be functioning normally ** \n \n");
				cout << "                        ~~~~~ Transcription has resumed ~~~~~" << endl;
				ribosome->setMessage("                    ** The ribosome is making +protien+ as normal **\n\n");
				ribosome->setItem("Protein");
			}
		}	
	}
}

void searchRoom(Room* current){
	string item_to_check = current->displayItem();
	if(item_to_check == ""){
		cout << "There is nothing to use in this organelle." << endl;
	}
	else
	cout << endl << "                    ~~~~~You find " << current->displayItem() << " in this organelle~~~~~" << endl << endl;
}

void displayBag(Room* current, Room* mitochondria, Mitochondria &mit, vector<string> &bag, int &energy_level){
	string choice;
	int x = 1;

	if (bag.empty() == true){
		cout << "Your bag is empty!" << endl;
	}
	else
	{
		for(vector<string>::const_iterator i = bag.begin(); i != bag.end(); ++i){
    		cout << "Your bag contains: " << endl;
    		cout << '[' << x <<  "] " << *i << endl;
			x++;
		}	
		cout << endl;
		cout << "Enter an item's number to use it, or press [B] to close your bag : ";
		getline(cin, choice);
		std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
		if (choice == "1"){
			useItem(current, mitochondria, mit, bag, bag[0], energy_level);
			bag.erase(bag.begin());
		}	
		if (choice == "2"){
			useItem(current, mitochondria, mit, bag, bag[1], energy_level);
			bag.erase(bag.begin()+1);
		}	
		if (choice == "3"){	
			useItem(current, mitochondria, mit, bag, bag[2], energy_level);
			bag.erase(bag.begin()+2);
		}	
		else if (choice != "b" && choice != "1" && choice != "2" && choice != "3"){
			cout << "Invalid input" << endl;
		}		
	}
}	

void useHook(Room* current, Room* mitochondria, vector<string> &bag, int energy_level){
	string item_to_check = current->displayItem();
	if(item_to_check == ""){
		cout << "Nothing to pick up" << endl;
	}
	if(item_to_check == "Foreign Matter"){
		cout << "You cant pick that up" << endl;
	}
	else{
		if(bag.size() < 4){
			bag.push_back(item_to_check);
			current->setItem("");
			cout << "                         ~~~~~You have picked up " << item_to_check << "~~~~~" << endl << endl;
		}
		else
			deleteItem(current, mitochondria, bag, energy_level);
	}		
}

void useItem(Room* &current, Room* &mitochondria, Mitochondria &mit, vector<string> &bag, string &item, int &energy_level){
	if (item == "Energy"){
		cout << "                    ~~~~~You have restored your energy level by 10~~~~~" << endl << endl;
		energy_level += 11;
	}

	if (item == "Protein"){
		if (current == mitochondria){
			mit.setProtein(1);
			cout << "   ~~~~~You have restored function to the mitochondria, and energy is abudant~~~~~\n";
			mitochondria->setMessage("              ~~~~The cell is functioning as normal, time to go before those full strength lysosomes find you~~~~~\n \n"); 
		    mitochondria->setMultiItem("Energy", "Energy", "Energy");           
		}
	}
	if (item == "Nitrogen" || item == "Oxygen"){
		cout << "                                ~~~~~It did nothing~~~~~ " << endl << endl;
	}
}

void deleteItem(Room *current, Room* mitochondria, vector<string> &bag, int energy_level){
	string choice;
	string confirm;
	string item_copy;
	int x = 1;

	cout << "Your bag is full." << endl;
	cout << "Your bag contains: " << endl;
	for(vector<string>::const_iterator i = bag.begin(); i != bag.end(); ++i){
    		
    		cout << '[' << x <<  "] " << *i << endl;
			x++;
	}
	cout << "What would you like to take out? " << endl;	
	getline(cin, choice);
	std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
	cout << "This item will be permanently destroyed. Are you sure you want to remove it? (y/n)" << endl;
	getline(cin, confirm);
	std::transform(confirm.begin(), confirm.end(), confirm.begin(), ::tolower);
if(confirm == "y"){
	if (choice == "1"){
		item_copy = bag[0];
		bag.erase(bag.begin());
	}
	if (choice == "2"){
		item_copy = bag[1];
		bag.erase(bag.begin()+1);
	}
	if (choice == "3"){
		item_copy = bag[2];
		bag.erase(bag.begin()+2);
	}
	else if (choice != "1" && choice != "2" && choice != "3" && choice != "y" && choice != "n"){
		cout << "Invalid input" << endl;
	}
}	

	cout << "You have taken out " << item_copy << endl; 
}

void displayMap(Room *current){	
cout << " - You are currently in the " << current->getName() << endl;
cout << endl << endl;
cout << "           ***************** MAP OF THE CELL *****************";
cout <<	endl;
cout <<	endl;		
cout << "                            |---------------|";
cout << endl;		
cout <<	"                            | Outside World |";
cout << endl;       
cout << "                            |---------------|";
cout << endl;           
cout <<	"                                    |";
cout << endl;           
cout <<	"                                  cell";
cout << endl;           
cout <<	"                                membrane";
cout << endl;           
cout <<	"                             x |         | x";
cout << endl;           
cout <<	"                               |_________|";
cout << endl;
cout <<	"                                    |";
cout << endl;
cout <<	"                       x            |            x";     
cout << endl;
cout <<	"                   lysosome     cytoplasm    ribosome";
cout << endl;
cout <<	"                   |       |   |         |   |       |";
cout << endl;
cout <<	"                 x |       |---|         |---|       | x";
cout << endl;
cout <<	"                   |_______|   |_________|   |_______|";
cout << endl;
cout <<	"                              /          \\     ";
cout << endl; 
cout <<	"        x              x     /      x      \\     x";
cout << endl;
cout <<	"   mitochondria     vacuole /   ___E.R___    \\_golgi_";
cout << endl;
cout <<	"     |      |      |       |   |         |   |       |";
cout << endl;
cout <<	"   x |      |------|       |---|         |---|       | x";
cout << endl;
cout <<	"     |______|      |_______|   |_________|   |_______|";
cout << endl;
cout <<	"        x             ^                          ^";
cout << endl;
cout <<	"                      |             |            |";
cout << endl;
cout <<	"                      |--------------------------|	";	 
cout << endl;
cout <<	"                                    |";
cout << endl;
cout <<	"                                 nuclear";
cout << endl;
cout <<	"                                envelope";
cout << endl;
cout <<	"                             x |         | x";
cout << endl;
cout <<	"                               |_________|";
cout << endl;
cout <<	"                                    |";
cout << endl;
cout <<	"                                    |              x";
cout << endl;
cout <<	"                                ~NUCLEUS~      nucleolus";
cout << endl;
cout <<	"                               {         }     |        |";
cout << endl;
cout <<	"                             x {         }-----|        |";
cout << endl;
cout <<	"                               {~~~~~~~~~}     |________|";
cout << endl;
cout << "                                    x               x";
cout << endl << endl;;
}