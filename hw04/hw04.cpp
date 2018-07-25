/*
    Michael Li
    hw04: pointer basics
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
    class Warrior:
        fields: string name
                float strength
                bool isHired
                bool isAlive
        methods: modifyStrength(float fract) - sets strength to fraction of strength
                 display() - prints name and strength
*/
class Warrior{
public:
    Warrior(const string& name, int str): name(name), strength(str), isHired(false), isAlive(true){
    }

    string getName() const{
        return name;
    }

    void setHiredStatus(bool status){
        isHired = status;
    }

    bool getHiredStatus() const{
        return isHired;
    }

    float getStrength() const{
        return strength;
    }

    void modifyStrength(float fract){
        strength = fract * strength;
    }

    void display() const{
        cout << "\t" << name << ": " << strength << endl;
    }

private:
    string name;
    float strength;
    bool isHired;
    bool isAlive;
};

/*
    class Noble:
        fields: string name
                vector<Warrior*> army
                bool isAlive
        methods: explained above method signature
*/
class Noble{
public:
    Noble(const string& name) : name(name), isAlive(true){
    }

    /*
        Purpose: pushes a Warrior* ptr to a vector<Warrior*>
        Parameters: Warrior& warrior -  the warrior to push
        Return Value: void
        Notes: checks if the warrior is already hired or if the noble is dead
    */
    void hire(Warrior& warrior){
        if (warrior.getHiredStatus()){
            cout << warrior.getName() << " has already been hired!" << endl;
            return;
        }

        if (!isAlive){
            cout << name << " is dead! He can't hire any warriors!" << endl;
            return;
        }

        Warrior* ptr = &warrior;
        army.push_back(ptr);
        warrior.setHiredStatus(true);
    }

    /*
        Purpose: removes a Warrior from vector<Warrior*> army
        Parameters: Warrior& warrior to remove
        Return Value: void
        Notes: checks if noble is alive
    */
    void fire(Warrior& warrior){
        if (!isAlive){
            cout << name << " is dead! He can't fire any warriors!" << endl;
        }else{
           for (size_t i = 0; i < army.size(); ++i){
                if (army[i] == &warrior){
                    cout << warrior.getName() << ", You're fired! -- " << name << endl;
                    pop_index(i);
                    warrior.setHiredStatus(false);
                    return;
                }
            }
            cout << name << " has not hired that warrior!" << endl;
        }
    }

    /*
        Purpose: calculates the strength of Noble's vector<Warrior*> army
        Parameters: None
        Return Value: float
    */
    float calcStrength() const{
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
            cout << "Mutual Annihilation: " << name << " and " << enemy.name << " die at each other's hands" << endl;
            return;
        }

        if (ownStr > enemyStr){
            enemy.isAlive = false;
            frac = 1 - (enemyStr/ownStr);
            for (size_t i = 0; i < army.size(); ++i){
                army[i]->modifyStrength(frac);
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

    /*
        Purpose: removes a Warrior from vector<warrior*> army
        Parameters: size_t index - index of Warrior to remove
        Return Value: void
    */
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

int main(){
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

	jim.display();
	lance.display();
	art.display();
	linus.display();
	billie.display();

	art.fire(cheetah);
	art.display();

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);
    return 0;
}
