/*
    hw02: structs, files, functions
    Michael Li
    Purpose: Model a game of medieval times
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Warrior{
    string name;
    int strength;

    Warrior(const string& name, const int& str){
        this->name = name;
        this->strength = str;
    }
};

void printStatus(const vector<Warrior>& warriors);
void makeWarrior(vector<Warrior>& warriors,const string& name,const int& strength);
size_t findWarrior(const string& name, const vector<Warrior>& warriors);
void battleWarriors(const string& warriorName1, const string& warriorName2, vector<Warrior>& warriors);

/*
    Purpose: print out the contents of a vector of Warrior
    Parameters: vector<Warrior> warriors - collection of warriors
    Return Value: void
*/
void printStatus(const vector<Warrior>& warriors){
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for(const Warrior& warrior: warriors){
        cout << "Warrior: " << warrior.name << ", strength: " << warrior.strength << endl;
    }
}

/*
    Purpose: Constructs a Warrior with given parameters and push it to back of a vector
    Parameters: vector<Warrior> warriors - collection of warriors
                string name - name of the Warrior to be created
                int strength - strength of Warrior to be created
    Return Value: void
*/
void makeWarrior(vector<Warrior>& warriors,const string& name,const int& strength){
    warriors.push_back(Warrior(name, strength));
}

/*
    Purpose: Find index of Warrior in collection with specified name
    Parameters: string name - name of Warrior to search for
                vector<Warrior> warriors - collection of warriors
    Return Value: size_t - index of warrior
*/
size_t findWarrior(const string& name, const vector<Warrior>& warriors){
    for (size_t i = 0; i < warriors.size(); ++i){
        if (warriors[i].name == name){
            return i;
        }
    }
    return warriors.size();
}

/*
    Purpose: Make two Warriors battle and potentially modify strengths of Warriors
    Parameters: string warriorName1 - name of first Warrior to search for
                string warriorName2 - name of second Warrior to search for
                vector<Warrior> warriors - collection of Warrior
    Return Value: void
*/
void battleWarriors(const string& warriorName1, const string& warriorName2, vector<Warrior>& warriors){
    cout << warriorName1 << " battles " << warriorName2 << endl;
    size_t war1 = findWarrior(warriorName1, warriors);
    size_t war2 = findWarrior(warriorName2, warriors);

    if (warriors[war1].strength == 0 and warriors[war2].strength == 0){
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
        return;
    }

    if (warriors[war1].strength == 0){
        cout << "He's dead, " << warriors[war2].name << endl;
        return;
    }

    if (warriors[war2].strength == 0){
        cout << "He's dead, " << warriors[war1].name << endl;
        return;
    }

    if (warriors[war1].strength > warriors[war2].strength){
        cout << warriors[war1].name << " defeats " << warriors[war2].name << endl;
        warriors[war1].strength = warriors[war1].strength - warriors[war2].strength;
        warriors[war2].strength = 0;
        return;
    }

    if (warriors[war2].strength > warriors[war1].strength){
        cout << warriors[war2].name << " defeats " << warriors[war1].name << endl;
        warriors[war2].strength = warriors[war2].strength - warriors[war1].strength;
        warriors[war1].strength = 0;
        return;
    }

    if (warriors[war2].strength == warriors[war1].strength){
        cout << "Mutual Annihilation: " << warriors[war1].name << " and " << warriors[war2].name << " die at each other's hands" << endl;
        warriors[war1].strength = 0;
        warriors[war2].strength = 0;
        return;
    }
}

int main()
{
    ifstream ifs("warriors.txt");
    //check if able to open file
    if (!ifs){
        cout << "cannot open file." << endl;
        exit(1);
    }else{
        vector<Warrior> warriorList;
        string word;
        string name;
        int str;
        string warrior1;
        string warrior2;

        //go through file to read commands
        while(ifs >> word){
            //respond accordingly based on command
            if (word == "Warrior"){
                ifs >> name;
                ifs >> str;
                makeWarrior(warriorList, name, str);
            }

            if (word == "Battle"){
                ifs >> warrior1;
                ifs >> warrior2;
                battleWarriors(warrior1, warrior2, warriorList);
            }

            if (word == "Status"){
                printStatus(warriorList);
            }
        }
        ifs.close();
    }
}
