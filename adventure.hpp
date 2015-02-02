#include <iostream>
#include <algorithm>
#include <vector>
#include <unistd.h> 
#include <iomanip>

using std::vector;
using std::endl;
using std::cout;
using std::string;
using std::cin;

class Room{
protected:
	string name;
	string description;
	string message;
	string item;
public:

	Room* northLink;
	Room* eastLink;
	Room* southLink;
	Room* westLink;
	
	Room(string n, string d);
	virtual void setMessage(string m){
		message = m;
	}
	virtual string displayMessage(){
		return message;
	}
	virtual void setItem(string i){
		item = i;
	}
	virtual string displayItem(){
		return item;
	}
	virtual void setMultiItem(string a, string b, string c){}
	void setProtein(int x);
	int getProtein();
	string getName();
	string getDescription();
	void assign(Room* &current_room, Room* north, Room* east, Room* south, Room* west);
};

class Mitochondria : public Room{
private:
	int protein;
public:
	Mitochondria(string x, string y) : Room (x, y){}  
	void setProtein(int x){
		protein = x;
	}
	int getProtein(){
		return protein;
	}
	void setMultiItem(string a, string b, string c){
		item = a;
		b = a;
		c = b;
	}

};

class Nucleus : public Room{
private:
	int junk;
public:
	Nucleus(string x, string y) : Room (x, y){}  
	void obstruction(int x){
		junk = x;
	}
};

class Ribosome : public Room{
	int protein;
public:
	Ribosome(string x, string y) : Room (x, y){}  
	
	void makeProtein(int x){
		protein = x;
	}
	int getProtein(){
		return protein;
	}
};

/*********************************************************************
** Function: animate
** Description: Displays simple animation as to signal moving from one
** room to the next
** Parameters: none
** Pre-Conditions: a movement from one room to the next
** Post-Conditions: displays the movement animation
*********************************************************************/ 
void animate();

/*********************************************************************
** Function: move
** Description: moves the current position based off of the NESW choice
** Parameters: string for direction, current Room pointer and temp Room pointer
** Pre-Conditions: requires sucessful if statement from navigation function
** Post-Conditions: reassigns current pointer
*********************************************************************/ 
void move(string direction, Room* &current, Room* &temp);

/*********************************************************************
** Function: navigation
** Description: calls the move function based off of user input
** Parameters: string path reference, Room current pointer and Room temp pointer
** Pre-Conditions: requires valid string input and initated Rooms
** Post-Conditions: sends info to move function to reassign current pointer
*********************************************************************/ 
void navigation(string &path, Room* &current, Room* &temp);

/*********************************************************************
** Function: checkInput
** Description: checks for valid user input
** Parameters: string reference
** Pre-Conditions: valid string
** Post-Conditions: returns if necessary the altered string or returns nothing
*********************************************************************/ 
void checkInput(string &input);

/*********************************************************************
** Function: checkEnergy
** Description: checks energy level for game over
** Parameters: int energy level value
** Pre-Conditions: initalized int value
** Post-Conditions: returns a saying based off of the energy value
*********************************************************************/ 
void checkEnergy(int energy_level);

/*********************************************************************
** Function: specialRoomCheck
** Description: checks for one of the "special" rooms
** Parameters: int energy level value
** Pre-Conditions: initalized int value
** Post-Conditions: returns a saying based off of the energy value
*********************************************************************/ 
void specialRoomCheck(Room* current, Mitochondria &mit, Room* mitochondria, Room* cytoplasm, Room* nucleus, Room* &ribosome, Room* &membrane, Room* outside);

/*********************************************************************
** Function: shootLaser
** Description: shoots the ship laser as to destroy any item in the room
** Parameters: current Room pointer, ribosome Room pointer, nucleus Room pointer
** Pre-Conditions: initialized room and room with item
** Post-Conditions: returns an emtpy room item ""
*********************************************************************/ 
void shootLaser(Room* current, Room* &ribosome, Room* &nucleus);

/*********************************************************************
** Function: searchRoom
** Description: searches the room for any items within
** Parameters: Room current pointer
** Pre-Conditions: initalized Room
** Post-Conditions: returns if anything is located in the room and what
*********************************************************************/ 
void searchRoom(Room* current);

/*********************************************************************
** Function: displayBag
** Description: displays the users current bag
** Parameters: current Room pointer, mitochondria Room, bag vector, int energy level
** Pre-Conditions: requires Initalized rooms, empty or full bag vector and energy level
** Post-Conditions: adds 1 to energy level so that using bag doesnt take energy, calls 
** useItem function if user wants to use an item
*********************************************************************/ 
void displayBag(Room* current, Room* mitochondria, Mitochondria &mit, vector<string> &bag, int &energy_level);

/*********************************************************************
** Function: useHook
** Description: picks up any items within the room
** Parameters: current Room pointer, mitochondria Room pointer, bag vector, int energy level
** Pre-Conditions: initalized Room pointers, bag with less than 3 items
** Post-Conditions: fills the bag with item that was in the room
*********************************************************************/ 
void useHook(Room* current, Room* mitochondria, vector<string> &bag, int energy_level);

/*********************************************************************
** Function: useItem
** Description: uses the selected item from the players bag
** Parameters: current Room pointer, mitochondria Room pointer, Mitochondra room, bag vector, string item choice, int energy level
** Pre-Conditions: initalized Room pointers, bag with at least 1 item, item choice to use
** Post-Conditions: essentially just deletes the item from the bag and 
** if the current room has special properties, they will change
*********************************************************************/ 
void useItem(Room* &current, Room* &mitochondria, Mitochondria &mit, vector<string> &bag, string &item, int &energy_level);

/*********************************************************************
** Function: deleteItem
** Description: deletes an item from the bag
** Parameters: current Room pointer, mitochondria Room pointer, bag vector, int energy level
** Pre-Conditions: initalized Room pointers, bag with 3 items
** Post-Conditions: deletes the selected item from the bag
*********************************************************************/ 
void deleteItem(Room *current, Room* mitochondria, vector<string> &bag, int energy_level);

/*********************************************************************
** Function: displayMap
** Description: displays the map of the cell
** Parameters: current Room pointer
** Pre-Conditions: initizlized room pointer
** Post-Conditions: prints out the map
*********************************************************************/ 
void displayMap(Room* current);
