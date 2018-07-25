#include "Noble.h"
#include "Warrior.h"

using namespace std;

namespace WarriorCraft{
    ostream& operator<<(ostream& os,const Noble& noble){
        os << noble.name << " has an army of " << noble.army.size() << endl;
        for (const Warrior* warrior: noble.army){
            os << *warrior;
        }
        return os;
    }

    const string& Noble::getName() const{
        return name;
    }

    /*
        Purpose: pushes a Warrior* ptr to a vector<Warrior*>
        Parameters: Warrior& warrior -  the warrior to push
        Return Value: void
        Notes: checks if the warrior is already hired or if the noble is dead
    */
    void Noble::hire(Warrior& warrior){
        if (warrior.getOwner()){
            cout << warrior.getName() << " has already been hired!" << endl;
            return;
        }

        if (!isAlive){
            cout << name << " is dead! He can't hire any warriors!" << endl;
            return;
        }

        Warrior* ptr = &warrior;
        army.push_back(ptr);
        warrior.setOwner(this);
    }

    /*
        Purpose: removes a Warrior from vector<Warrior*> army
        Parameters: Warrior& warrior to remove
        Return Value: void
        Notes: checks if noble is alive
    */
    void Noble::fire(Warrior& warrior){
        if (!isAlive){
            cout << name << " is dead! He can't fire any warriors!" << endl;
        }
        else{
            for (size_t i = 0; i < army.size(); ++i){
                if (army[i] == &warrior){
                    cout << "You don't work for me anymore, " << warrior.getName() << "! -- " << name << endl;
                    pop_index(i);
                    warrior.setOwner(nullptr);
                    return;
                }
            }
            cout << name << " has not hired that warrior!" << endl;
        }
    }

    /*
        Purpose: removes the escaped Warrior from army
        Parameters: Warrior* warrior that escaped
        Return Value: None
    */
    void Noble::warriorEscape(Warrior* warrior){
        for (size_t i = 0; i < army.size(); ++i){
            if (army[i] == warrior){
                pop_index(i);
                return;
            }
        }
    }

    /*
        Purpose: calculates the strength of Noble's vector<Warrior*> army
        Parameters: None
        Return Value: float
    */
    float Noble::calcStrength() const{
        float totalStr = 0;
        for (size_t war = 0; war < army.size(); ++war){
            totalStr += army[war]->getStrength();
        }
        return totalStr;
    }

    /*
        Purpose: conducts battle between two Nobles
        Parameters: Noble& enemy - Noble to fight
        Return Value: void
    */
    void Noble::battle(Noble& enemy){
        float ownStr;
        float enemyStr;
        float frac;

        cout << name << " battles " << enemy.name << endl;

        if(!isAlive and !enemy.isAlive){
            cout << "Oh, NO!  They're both dead!  Yuck!"<< endl;
            return;
        }

        if(!isAlive){
            cout << "He's dead, " << enemy.name << endl;
            return;
        }

        if(!enemy.isAlive){
            cout << "He's dead, " << name << endl;
            return;
        }

        ownStr = calcStrength();
        enemyStr = enemy.calcStrength();

        if (ownStr == enemyStr){
            isAlive = false;
            enemy.isAlive = false;

            for (size_t i = 0; i < army.size(); ++i){
                army[i]->modifyStrength(0);
            }

            for (size_t i = 0; i < enemy.army.size(); ++i){
                enemy.army[i]->modifyStrength(0);
            }
            cout << "Mutual Annihilation: " << name << " and " << enemy.name << " die at each other's hands" << endl;
            return;
        }

        if (ownStr > enemyStr){
            enemy.isAlive = false;
            frac = 1 - (enemyStr/ownStr);
            for (size_t i = 0; i < army.size(); ++i){
                army[i]->modifyStrength(frac);
            }

            for (size_t i = 0; i < enemy.army.size(); ++i){
                enemy.army[i]->modifyStrength(0);
            }
            cout << name << " defeats " << enemy.name << endl;
            return;
        }

        if (enemyStr > ownStr){
            isAlive = false;
            frac = 1 - (ownStr/enemyStr);
            for (size_t i = 0; i < enemy.army.size(); ++i){
                enemy.army[i]->modifyStrength(frac);
            }

            for (size_t i = 0; i < army.size(); ++i){
                army[i]->modifyStrength(0);
            }

            cout << enemy.name << " defeats " << name << endl;
            return;
        }
    }

    void Noble::display() const{
        cout << name << " has an army of " << army.size() << endl;

        for(size_t i = 0; i < army.size(); ++i)
        {
            army[i]->display();
        }
    }

    void Noble::pop_index(size_t index){
        army[index] = nullptr;
        //can i put an int to size_t?
        Warrior* ptrHolder;
        //moves the one to delete to the back and deletes
        for(size_t i = index; i < army.size()-1; ++i)
        {
            ptrHolder = army[i];
            army[i] = army[i+1];
            army[i+1] = ptrHolder;
        }
        army.pop_back();
    }
};
