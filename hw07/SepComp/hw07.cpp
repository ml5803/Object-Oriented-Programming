#include "Noble.h"
#include "Protector.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace WarriorCraft;

int main(){
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hire(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250); 	
    joe.battle(randy);	
    joe.battle(sam);	
    Lord janet("Janet");	
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hire(hardy);	
    janet.hire(stout);	
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);	
    janet.battle(barclay);	
    janet.hire(samantha);	
    Archer pethora("Pethora", 50);	
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hire(pethora);
    janet.hire(thora);
    sam.hire(merlin);
    janet.battle(barclay);	
    sam.battle(barclay);	
    joe.battle(barclay);
	
	// Archer james("james",10);
	// Swordsman bob("bob",10);
	// Archer filler("filler",10);
	// PersonWithStrengthToFight jim("jim",5);
	// Lord lord1("lord");
	// Lord lord2("lord2");
	// lord1.hire(james);
	// lord2.hire(bob);
	// jim.battle(lord2);
	
	// cout << jim.getAlive() << endl;
	// cout << lord2.getAlive() << endl;
	// cout << bob.getStr() << endl;
	// cout << lord2.getStr() << endl;
	// lord2.fire(bob);
	// cout << lord2.getStr() << endl;
	// lord1.hire(bob);
	// cout << lord1.getStr() << endl;
	// lord2.hire(filler);
	// lord1.battle(lord2);
	
}
