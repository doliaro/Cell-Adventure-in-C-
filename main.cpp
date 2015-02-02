
/*********************************************************************
** Program Filename: Cell Explorer

** Author: Dominic Oliaro

** Date: December 9, 2014

** Description: This is a simple game where the goal is find the problems 
** within the cell and fix them so that it works normally
*********************************************************************/
#include "adventure.hpp"


int main(int argc, char const *argv[])
{
	Room *current;
	Room *temp;

	Room out("Outside World", "                                 The world consists of many things");
	Room *outside = &out;

	Room mem("Cell Membrane ", "             The cell membrane is the cell's first line of defense.\n    It allows few things in (nutrients) and few things out (waste). But I guess it let you in?");
	Room *membrane = &mem;

	Room cyto("Cytoplasm ", "             The cytoplasm is the cell's internal environment.\n                It also keeps the organelles from bumping into each other.");
	Room *cytoplasm = &cyto;
	cytoplasm->setItem("Nitrogen");

	Room lys("Lysosome ", "Lysosomes are sacs with enzymes for digesting food that enter into the cell.");
	Room *lysosome = &lys;

	Ribosome rib("Ribosome", "Ribosomes use RNA copied from the nucleus and amino acids to make +proteins+");
	Room *ribosome = &rib;
	ribosome->setMessage("                ** This ribosome appears to not be making +proteins+. \n                    It may not be getting mRNA from the +nucleus+ ** \n\n");

	Room ret("Endoplasmic Reticulum", "The E.R. helps with transport of proteins made by the ribosomes, much like a conveyor belt.");
	Room *reticulum = &ret;
	Room golg("Golgi Apparatus", "The golgi apparatus modifies and exports proteins from the E.R., like a post office\n              It also aids in the creation of lysosomes and transport of lipids");
	Room *golgi = &golg;
	golgi->setItem("Oxygen");

	//special room 1
	Mitochondria mit("Mitochondrion", "Mitochondria turn sugar into +energy+ (ATP) that’s usable by the cell (and intruders).");
	mit.setProtein(0);
	Room *mitochondria = &mit;
	mitochondria->setMessage("                ** You notice this mitochondria isn't producing +energy+... \n                It appears that it's +protein+ structure may be damaged **\n\n");
	mitochondria->setItem("Energy");

	Room vac("Vacuole", "           A vaculoe is a storage container for waste or food");
	Room *vacuole = &vac;
	vacuole->setItem("Oxygen");

	Room envelope("Nuclear Envelope", "   The nuclear envelope is a membrane even more selective than the cell membrane.\n              Usually only nucleic acids and some proteins are allowed in and out.");
	Room *nuclear_envelope = &envelope;

	Nucleus nuc("Nucleus", "                 This is the command center of the cell \n  Everything that happens in the cell is controlled by the nucleus and the DNA inside.");
	Room *nucleus = &nuc;
	nuc.obstruction(1);
	nucleus->setItem("Foreign Matter");
	nucleus->setMessage("                  ** There appears to be a problem within the nucleus \n     +Something+ is blocking transcription (copying of DNA to RNA) from occuring \n                  and the ribosomes aren't able to make +protein+ ** \n\n ");
	
	Room nucleo("Nucleolus", "Primarily makes ribosomes");
	Room *nucleolus = &nucleo;

	outside->assign(outside, NULL, NULL, membrane, NULL);
	membrane->assign(membrane, NULL, NULL, cytoplasm, NULL);
	cytoplasm->assign(cytoplasm, membrane, ribosome, NULL, lysosome);
	lysosome->assign(lysosome, NULL, cytoplasm, vacuole, NULL);
	ribosome->assign(ribosome, NULL, NULL, golgi, cytoplasm);
	reticulum->assign(reticulum, NULL, golgi, nuclear_envelope, vacuole);
	golgi->assign(golgi, cytoplasm, NULL, vacuole, reticulum);
	vacuole->assign(vacuole, cytoplasm, reticulum, golgi, mitochondria);
	mitochondria->assign(mitochondria, cytoplasm, vacuole, cytoplasm, cytoplasm);
	nuclear_envelope->assign(nuclear_envelope, reticulum, NULL, nucleus, NULL);
	nucleus->assign(nucleus, nuclear_envelope, nucleolus, NULL, NULL);
	nucleolus->assign(nucleolus, NULL, NULL, NULL, nucleus);

	current = outside;


	cout << "                 |################################################################|" << endl;
	cout << "                 |                                                                |" << endl;
	cout << "                 |                    Welcome to Cell Explorer                    |"	<< endl;
	cout << "                 |                                                                |" << endl;
	cout << "                 |################################################################|" << endl;
	cout << endl << endl << endl << endl;
	cout << "                               *********** OUTSIDE WORLD ***********" << endl;    
	cout << current->getDescription() << endl << endl <<endl;
	cout << "                           Your mission, should you choose to accept it,\n";
	cout << "                     involves fixing one of many malfunctioning cells that are" << endl;
	cout << "                   reproducing as destructive cells within the human population. " << endl;
	cout << "                            If you can figure out a way to fix one cell " << endl;
	cout << "                                 we should be able to fix the rest. " << endl;      
	cout << endl;
	cout << "                            Your size will be reduced to that of a virus " << endl;
	cout << "                     and you will enter the cell in a highly specified nanobot. " << endl << endl;

	cout << "                                 Your energy levels are limited" << endl;
	cout << "                         You will have a bag that can carry max [3] items" << endl;
	cout << "                                            Good luck." << endl << endl;
	cout << "                                 Press any key to enter the cell" << endl;

	string anykey;
	string path;
	vector<string> bag;
	bag.push_back("Energy");
	int energy_level = 25;

	getline(cin, anykey);

	//Move into cell membrane to begin
	move("s", current, temp);
	cout << "Enter X at anytime to exit" << endl;

	//Loop that runs the game
	while(path != "x"){
	
	cout << " NAVIGATE    " << "  MAP" << "    BAG" << "    HOOK" << "    LASER" << "    SEARCH";
	checkEnergy(energy_level);
	cout << "   [N]" << "         [M]" << "    [B]" << "     [H]"  << "     [L]" <<  "      [F]" << endl;
	cout << "[W]"; 
	cout << "   [E]" << endl;
	cout << "   [S]" << endl;
	cout << endl;
	cout << "--> ";

	getline(cin, path);
	std::transform(path.begin(), path.end(), path.begin(), ::tolower);
	checkInput(path);

		if (current == membrane){
			if(path == "n" || path == "e" || path == "w"){
			cout << "Do you want to leave the cell and exit back into the world? (y/n) "<< endl;
			string choice;
			getline(cin, choice);
			std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
			checkInput(choice);

				if (choice == "y"){
					int mit_protein = mit.getProtein();
					if (mit_protein == 1){
						cout << "\n\n     ~~~~~ YOU HAVE ESCAPED THE CELL AND SAVED THE WORLD, GOOD JOB! ~~~~~~ \n\n";
						exit(0);
					}
					else
						exit(0);
				}
			}	
		}
		if (current == NULL){
		current = temp;
		}

		navigation(path, current, temp);
		specialRoomCheck(current, mit, mitochondria, cytoplasm, nucleus, ribosome, membrane, outside);
		energy_level--;	

		if (path == "m") {displayMap(temp); energy_level++;}
		if (path == "x") {exit(0);}
		if (path == "b") {displayBag(current, mitochondria, mit, bag, energy_level); energy_level++;}
		if (path == "l") {shootLaser(current, ribosome, nucleus);}
		if (path == "h") {useHook(current, mitochondria, bag, energy_level);}
		if (path == "f") {searchRoom(temp);}
		
	}//end exit while loop
	return 0;
}

