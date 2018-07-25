/*
    Michael Li
    hw05: dynamic memory
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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

    ~Noble(){
        while(army.size() != 0){
            delete army[army.size()-1];
            army.pop_back();
        }
    }

    string getName() const{
        return name;
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
        Parameters: vector<Warrior*> warriorList - where to fire the Warrior to
                    string warName - name of Warrior to fire
        Return Value: void
        Notes: checks if noble is alive
    */
    Warrior* fire(const string& warName){
        if (!isAlive){
            cout << name << " is dead! He can't fire any warriors!" << endl;
        }else{
           for (size_t i = 0; i < army.size(); ++i){
                if (army[i]->getName() == warName){
                    cout << "You don't work for me anymore, " << warName << "! -- " << name << endl;
                    army[i]->setHiredStatus(false);
                    Warrior* warPtr = army[i];
                    pop_index(i);
                    return warPtr;
                }
            }
            cout << name << " has not hired that warrior!" << endl;
            return nullptr;
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

/*
    Purpose: finds the index of a Noble object by name
    Parameters: const vector<Noble*>& nobles - vector to look through
                const string& name - name to look for
    Return Value: size_t
*/
size_t findNoble(const vector<Noble*>& nobles, const string& name){
    for(size_t i = 0; i < nobles.size(); ++i){
        if (nobles[i]->getName() == name){
            return i;
        }
    }
    return nobles.size();
}

/*
    Purpose: finds the index of a Warrior object by name
    Parameters: const vector<Warrior*>& warriors - vector of Warrior* to look through
                const string& name - name to look for
    Return Value: size_t
*/
size_t findWarrior(const vector<Warrior*>& warriors, const string& name){
    for(size_t i = 0; i < warriors.size(); ++i){
        if (warriors[i]->getName() == name){
            return i;
        }
    }
    return warriors.size();
}

void popIndexWarriorsPtr(vector<Warrior*>& warriorList, size_t index){
        warriorList[index] = nullptr;
        Warrior* ptrHolder;
        //moves the one to delete to the back and deletes
        for(size_t i = index; i < warriorList.size()-1; ++i){
            ptrHolder = warriorList[i];
            warriorList[i] = warriorList[i+1];
            warriorList[i+1] = ptrHolder;
        }
        warriorList.pop_back();
}

/*
    Purpose: displays the content of a Noble vector and a Warrior vector
    Parameters: const vector<Noble*>& nobleList - vector of Noble* ptr to use to display Noble objects
                const vector<Warrior*> warriorList - vector of Warrior* ptr to use to display Warrior objects
    Return Value: void
*/
void printStatus(const vector<Noble*>& nobleList, const vector<Warrior*> warriorList){
    cout << "Status" << endl << "======" << endl << "Nobles:" << endl;
    if (nobleList.size() != 0){
        for (const Noble* nob: nobleList){
            nob->display();
        }
    }else{
        cout << "NONE" << endl;
    }

    cout << "Unemployed Warriors:" << endl;

    if (warriorList.size() != 0){
        for (const Warrior* war: warriorList){
            war->display();
        }
    }else{
        cout << "NONE" << endl;
    }
}

int main(){
    //set up necessary variables
    ifstream ifs("nobleWarriors.txt");
    string command;
    string name1;
    string name2;
    int str;

    vector<Noble*> nobleList;
    vector<Warrior*> warriorList;
    size_t noblePos1;
    size_t noblePos2;
    size_t warPos;

    //check if able to open file
    if(!ifs){
        cout << "unable to open file" << endl;
        exit(1);
    }else{
        while (ifs >> command){
            //create new Noble
            if (command == "Noble"){
                ifs >> name1; // noble
                if(findNoble(nobleList,name1) == nobleList.size()){
                    nobleList.push_back(new Noble(name1));
                }else{
                    cout << "A noble already exists with that name!" << endl;
                }
            }

            //create new Warrior
            if (command == "Warrior"){
                ifs >> name1; //warrior
                ifs >> str;
                if(findWarrior(warriorList,name1) == warriorList.size()){
                    warriorList.push_back(new Warrior(name1, str));
                }else{
                    cout << "A warrior already exists with that name!" << endl;
                }
            }

            if (command == "Hire"){
                ifs >> name1; //noble
                ifs >> name2; //warrior

                noblePos1 = findNoble(nobleList,name1);
                warPos = findWarrior(warriorList,name2);
                if(noblePos1 == nobleList.size()){
                    cout << "This noble doesn't exist!" << endl;
                }

                if(warPos == warriorList.size()){
                    cout << "This warrior cannot be hired!" << endl;
                }

                if(noblePos1 < nobleList.size() && warPos < warriorList.size()){
                    nobleList[noblePos1]->hire(*warriorList[warPos]);
                    popIndexWarriorsPtr(warriorList, warPos);
                }
            }

            if (command == "Fire"){
                ifs >> name1; //noble
                ifs >> name2; //warrior

                if(noblePos1 == nobleList.size()){
                    cout << "This noble doesn't exist!" << endl;
                }

                if(noblePos1 < nobleList.size()){
                    warriorList.push_back(nobleList[noblePos1]->fire(name2));
                }
            }

            if (command == "Battle"){
                ifs >> name1; //noble1
                ifs >> name2; //noble2

                noblePos1 = findNoble(nobleList,name1);
                noblePos2 = findNoble(nobleList,name2);
                if(noblePos1 == nobleList.size()){
                    cout << name1 << " doesn't exist!" << endl;
                }

                if(noblePos2 == nobleList.size()){
                    cout << name2 << " doesn't exist!" << endl;
                }

                if(noblePos1 < nobleList.size() && noblePos2 < nobleList.size()){
                    nobleList[noblePos1]->battle(*nobleList[noblePos2]);
                }
            }

            if (command == "Status"){
                printStatus(nobleList, warriorList);
            }

            if (command == "Clear"){
                //loops through both the vectors backwards, deletes the object at memory address and removes pointers
                while(nobleList.size() != 0){
                    delete nobleList[nobleList.size()-1];
                    nobleList.pop_back();
                }

                while(warriorList.size() != 0){
                    delete warriorList[warriorList.size()-1];
                    warriorList.pop_back();
                }
            }
        }
    }
    ifs.close();
}
