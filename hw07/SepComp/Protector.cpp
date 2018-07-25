#include "Noble.h"
#include "Protector.h"

using namespace std;

namespace WarriorCraft{
	const string& Protector::getName() const{
		return name;
	}

	Lord* Protector::getOwner() const{
		return owner;
	}

	void Protector::setOwner(Lord* ptr){
		owner = ptr;
	}

	float Protector::getStr(){
		return strength;
	}

	void Protector::battlecry() const{
		cout << getName() << " says: Take that in the name of my lord, " << owner->getName() << "!" << endl;
	}
	
	//sets strength according to battle
	void Protector::modifyStrength(float frac){
		strength = strength * frac;
	}

	//Protector runs away from Lord, removes ptr from army
	void Protector::runaway(){
		if(Protector::getOwner()){
			cout << Protector::getName() << " flees in terror, abandoning his lord, " << owner->Noble::getName() << endl;
			owner->Lord::protectorEscape(this);
		}else{
			cout << "I don't have an owner! I want one!" << endl;
		}
	}
	
	bool Protector::getAlive() const{
		return isAlive;
	}
	
	void Protector::setAlive(bool status){
		isAlive = status;
	}

	void Wizard::battlecry() const{
		if(Protector::getAlive()){
			cout << "POOF" << endl;
		}
	}

	void Swordsman::battlecry() const{
		if(Protector::getAlive()){
			cout << "CLANG! ";
			Protector::battlecry();
		}
	}

	void Archer::battlecry() const{
		if(Protector::getAlive()){
			cout << "TWANG! ";
			Protector::battlecry();
		}
	}
}



