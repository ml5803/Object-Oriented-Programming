/*
    hw03: encapsulation, data hiding and delegation
    Michael Li
    Purpose: to model a game of medieval times - with classes
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/*
    class Warrior:
        public methods: printStatus(), getter and setters for private name and weapon
        private: name and weapon
                 Weapon class with getter and setter for weapon name and weapon str

*/
class Warrior{
public:
    Warrior(const string& warriorName, const string& weaponName, int weaponStr): warriorName(warriorName), weapon(Weapon(weaponName,weaponStr)){
    };

    void printStatus() const {
        cout << "Warrior: " << warriorName << ", weapon: " << weapon.getWeaponName() << ", " << weapon.getWeaponStr() << endl;
    }

    string getName() const{
        return warriorName;
    }

    int getWeaponStr() const{
        return weapon.getWeaponStr();
    }

    void setWeaponStr(int str){
        weapon.setWeaponStr(str);
    }

private:
    class Weapon{
    public:
        Weapon(const string& wName, int str): wName(wName), str(str){
        }

        string getWeaponName() const{
            return wName;
        }

        int getWeaponStr() const{
            return str;
        }

        void setWeaponStr(int str){
            this->str = str;
        }
    private:
        string wName;
        int str;
    };

    string warriorName;
    Weapon weapon;
};

void printStatus(const vector<Warrior*>& warriors);
size_t findWarrior(const string& name, const vector<Warrior*> warriors);
void battleWarriors(const string& warriorName1, const string& warriorName2,const vector<Warrior*>& warriors);

/*
    Purpose: Print out  the object of pointers in a vector of Warrior pointers
    Parameters: vector<Warrior*>& warriors - vector of Warrior pointers
    Return Value: void
*/
void printStatus(const vector<Warrior*>& warriors){
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for (const Warrior* warrior: warriors){
        //uses delegation to have each warrior to print own status
        warrior->printStatus();
    }
}

/*
    Purpose: Find index of correct Warrior pointer in collection of specified name
    Parameters: string name - name of warrior to look for
                vector<Warriors*> warriors - collection of Warrior pointers to look through
    Return Value: size_t i - index of Warrior pointer
*/
size_t findWarrior(const string& name, const vector<Warrior*> warriors){
    for (size_t i = 0; i < warriors.size(); ++i){
        if (warriors[i]->getName() == name){
            return i;
        }
    }
    return warriors.size();
}

/*
    Purpose: Make two warriors battle and potentially modify the strength of warriors' weapons.
    Parameters: string warriorName1 - name of first warrior to search for
                string warriorName2 - name of second warrior to search for
                vector<Warrior*> warriors - collection of Warrior pointers
    Return Value: void
*/
void battleWarriors(const string& warriorName1, const string& warriorName2,const vector<Warrior*>& warriors){
    cout << warriorName1 << " battles " << warriorName2 << endl;
    size_t war1 = findWarrior(warriorName1, warriors);
    size_t war2 = findWarrior(warriorName2, warriors);

    if (war1 == warriors.size()){
        cout << warriorName1 << " doesn't exist!" << endl;
        return;
    }

    if (war2 == warriors.size()){
         cout << warriorName2 << " doesn't exist!" << endl;
    }

    if (warriors[war1]->getWeaponStr() == 0 and warriors[war2]->getWeaponStr() == 0){
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
        return;
    }

    if (warriors[war1]->getWeaponStr() == 0){
        cout << "He's dead, " << warriors[war2]->getName() << endl;
        return;
    }

    if (warriors[war2]->getWeaponStr() == 0){
        cout << "He's dead, " << warriors[war1]->getName() << endl;
        return;
    }

    if (warriors[war1]->getWeaponStr() > warriors[war2]->getWeaponStr()){
        cout << warriors[war1]->getName() << " defeats " << warriors[war2]->getName() << endl;
        warriors[war1]->setWeaponStr(warriors[war1]->getWeaponStr() - warriors[war2]->getWeaponStr());
        warriors[war2]->setWeaponStr(0);
        return;
    }

    if (warriors[war2]->getWeaponStr()> warriors[war1]->getWeaponStr()){
        cout << warriors[war2]->getName() << " defeats " << warriors[war1]->getName() << endl;
        warriors[war2]->setWeaponStr(warriors[war2]->getWeaponStr() - warriors[war1]->getWeaponStr());
        warriors[war1]->setWeaponStr(0);
        return;
    }

    if (warriors[war2]->getWeaponStr() == warriors[war1]->getWeaponStr()){
        cout << "Mutual Annihilation: " << warriors[war1]->getName() << " and " << warriors[war2]->getName() << " die at each other's hands" << endl;
        warriors[war1]->setWeaponStr(0);
        warriors[war2]->setWeaponStr(0);
        return;
    }
}

int main()
{
    ifstream ifs("warriors.txt");
    //check if able to open file
    if (!ifs){
        cout << "unable to open file." << endl;
        exit(1);
    }else{
        string command;
        string warrior1;
        string warrior2;
        string weaponName;
        int weaponStr;
        vector<Warrior*> warriors;

        //go through file to read commands
        while (ifs >> command){
            // respond accordinly based on command
            if (command == "Warrior"){
                ifs >> warrior1;
                ifs >> weaponName;
                ifs >> weaponStr;
                Warrior* warPtr = new Warrior(warrior1,weaponName,weaponStr);
                warriors.push_back(warPtr);
            }

            if (command == "Battle"){
                ifs >> warrior1;
                ifs >> warrior2;
                battleWarriors(warrior1, warrior2, warriors);
            }

            if (command == "Status"){
                printStatus(warriors);
            }
        }
        //exit when done
        ifs.close();
    }
}
