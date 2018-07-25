#include "Noble.h"
#include "Protector.h"

using namespace std;
namespace WarriorCraft{
	const string& Noble::getName() const{
		return name;
	}

	//Two Nobles battle and have Protectors in respective armies do their battlecries. Sets status accordingly.
	void Noble::battle(Noble& enemy){
			if (&enemy == this){
				cout << "I can't fight myself >:(!" << endl;
				return;
			}
			float ownStr;
			float enemyStr;
			float frac;

			cout << Noble::getName() << " battles " << enemy.Noble::getName() << endl;
			
			if(!Noble::getAlive() and !enemy.Noble::getAlive()){
				cout << "Oh, NO!  They're both dead! Yuck!" << endl;
				return;
			}

			if(!Noble::getAlive()){
				cout << "He's dead, " << enemy.Noble::getName() << endl;
				return;
			}

			if(!enemy.Noble::getAlive()){
				cout << "He's dead, " << Noble::getName() << endl;
				return;
			}
			
			defend();
			enemy.defend();
			
			ownStr = getStr();
			enemyStr = enemy.getStr();

			if (ownStr == enemyStr){
				setAlive(false);
				enemy.setAlive(false);
				setStr(0);
				enemy.setStr(0);
				cout << "Mutual Annihilation: " << Noble::getName() << " and " << enemy.Noble::getName() << " die at each other's hands" << endl;
				return;
			}

			if (ownStr > enemyStr){
				enemy.setAlive(false);
				enemy.setStr(0);
				frac = 1 - (enemyStr/ownStr);
				setStr(frac);
				cout << Noble::getName() << " defeats " << enemy.Noble::getName() << endl;
				return;
			}

			if (enemyStr > ownStr){
				setAlive(false);
				setStr(0);
				frac = 1 - (ownStr/enemyStr);
				enemy.setStr(frac);
				cout << enemy.Noble::getName() << " defeats " << Noble::getName() << endl;
				return;
			}	
	}

	bool Noble::getAlive() const{
		return isAlive;
	}

	void Noble::setAlive(bool status){
		isAlive = status;
	}
	
	//Nobles by default do nothing when defending. Overridden in Lord
	void Noble::defend() const{
		return;
	}

	float PersonWithStrengthToFight::getStr() const{
		return strength;
	}

	void PersonWithStrengthToFight::setStr(float frac){
		strength = strength * frac;
	}

	//Loops through Lord's army and calculates his strength
	float Lord::calcStrength() const{
		float totalStr = 0;
		for (size_t prot = 0; prot < army.size(); ++prot){
			totalStr += army[prot]->getStr();
		}
		return totalStr;
	}

	float Lord::getStr() const{
		return calcStrength();
	}
	
	//If a Lord changes status, his army also changes
	void Lord::setAlive(bool status){
		Noble::setAlive(status);
		for (size_t prot = 0; prot < army.size(); ++prot){
			army[prot]->setAlive(status);
		}
	}
	
	//Delegates Protectors to fight... well, battlecry
	void Lord::defend() const{
		for (size_t prot = 0; prot < army.size(); ++prot){
			army[prot]->battlecry();
		}
	}

	//Sets strength with result according to battle
	void Lord::setStr(float frac){
		for(size_t i = 0; i < army.size(); ++i){
			army[i]->modifyStrength(frac);
		}
	}

	//Looks for a Protector in army, if found, fire him
	void Lord::fire(Protector& protector){
		 if (!Noble::getAlive()){
				cout << Noble::getName() << " is dead! He can't fire any warriors!" << endl;
			}
			else{
				for (size_t i = 0; i < army.size(); ++i){
					if (army[i] == &protector){
						pop_index(i);
						cout << "You don't work for me anymore, " << protector.getName() << "! -- " << Noble::getName() << endl;
						protector.setOwner(nullptr);
						return;
					}
				}
				cout << Noble::getName() << " has not hired that warrior!" << endl;
			}
	}

	//Checks if a Protector is available for hire, if is, hire him
	void Lord::hire(Protector& protector){
		if (protector.getOwner()){
			cout << protector.getName() << " has already been hired!" << endl;
			return;
		}
		
		if(!protector.getAlive()){
			cout << "Can't hire a corpse!" << endl;
		}
		
		if (!Noble::getAlive()){
			cout << Noble::getName() << " is dead! He can't hire any warriors!" << endl;
			return;
		}

		Protector* ptr = &protector;
		army.push_back(ptr);
		protector.setOwner(this);
	}

	//Escaped Protector are no longer in army.
	void Lord::protectorEscape(Protector* pPtr){
		for (size_t i = 0; i < army.size(); ++i){
			if (army[i] == pPtr){
				pop_index(i);
				return;
			}
		}
	}
	
	
	//Removes Protector* from army.
	void Lord::pop_index(size_t index){
		army[index] = nullptr;
        Protector* ptrHolder;
        //moves the one to delete to the back and deletes
        for(size_t i = index; i < army.size()-1; ++i)
        {
            ptrHolder = army[i];
            army[i] = army[i+1];
            army[i+1] = ptrHolder;
        }
        army.pop_back();
	}
}



