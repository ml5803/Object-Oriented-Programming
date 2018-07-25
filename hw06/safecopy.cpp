//#include "Noble.h"
//#include "Warrior.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
//using namespace WarriorCraft;

class Warrior;
class Noble;

class Warrior{
public:
    friend ostream& operator<<(ostream& os,const Warrior& war){
        os << "\t" << war.name << ": " << war.strength << endl;
        return os;
    }

    Warrior(const string& name, int str): name(name), strength(str), owner(nullptr), isAlive(true){
    }

    string getName() const{
        return name;
    }

    void setOwner(Noble* noble){
        owner = noble;
    }

    bool getOwner() const{
        return owner;
    }

    float getStrength() const{
        return strength;
    }

    void modifyStrength(float fract){
        strength = fract * strength;
    }
    void runaway();

    void display() const{
        cout << "\t" << name << ": " << strength << endl;
    }

private:
    string name;
    float strength;
    Noble* owner;
    bool isAlive;
};

class Noble{
public:
    friend ostream& operator<<(ostream& os, Noble noble){
        os << noble.name << " has an army of " << noble.army.size() << endl;
        for (const Warrior* warrior: noble.army){
            os << *warrior;
        }
        return os;
    }

    Noble(const string& name) : name(name), isAlive(true){
    }

    string getName() const{
        return name;
    }

    void hire(Warrior& warrior){
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

    void fire(Warrior& warrior){
        if (!isAlive){
            cout << name << " is dead! He can't fire any warriors!" << endl;
        }else{
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

    void warriorEscape(Warrior* warrior){
        for (size_t i = 0; i < army.size(); ++i){
            if (army[i] == warrior){
                pop_index(i);
                return;
            }
        }
    }

    float calcStrength() const{
        float totalStr = 0;
        for (size_t war = 0; war < army.size(); ++war){
            totalStr += army[war]->getStrength();
        }
        return totalStr;
    }

    void battle(Noble& enemy){
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

    void display() const {
        cout << name << " has an army of " << army.size() << endl;

        for(size_t i = 0; i < army.size(); ++i){
            army[i]->display();
        }
    }
private:
    string name;
    vector<Warrior*> army;
    bool isAlive;

    void pop_index(size_t index){
        army[index] = nullptr;
        //can i put an int to size_t?
        Warrior* ptrHolder;
        //moves the one to delete to the back and deletes
        for(size_t i = index; i < army.size()-1; ++i){
            ptrHolder = army[i];
            army[i] = army[i+1];
            army[i+1] = ptrHolder;
        }
        army.pop_back();
    }
};

void Warrior::runaway(){
    if(owner){
        cout << name << " flees in terror, abandoning his lord, " << owner->getName() << endl;
        owner->warriorEscape(this);
    }else{
        cout << "I don't have an owner! I want one!" << endl;
    }
}
int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);

    cout << jim;
    cout << lance;
	cout << art;
    cout << linus;
    cout << billie;

    cheetah.runaway();
    cout << art;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);
}
