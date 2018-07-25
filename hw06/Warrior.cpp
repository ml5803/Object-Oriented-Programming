#include "Noble.h"
#include "Warrior.h"

using namespace std;

namespace WarriorCraft{
    ostream& operator<<(ostream& os,const Warrior& war){
        os << "\t" << war.name << ": " << war.strength << endl;
        return os;
    }

    const string& Warrior::getName() const{
            return name;
    }

    void Warrior::setOwner(Noble* noble){
            owner = noble;
    }

    bool Warrior::getOwner() const{
            return owner;
    }

    float Warrior::getStrength() const{
            return strength;
    }

    void Warrior::modifyStrength(float fract){
            strength = fract * strength;
    }

    /*
        Purpose: Sets Noble* owner to nullptr, allows Warrior to escape from owner's army
        Parameters: None
        Return Value: None
    */
    void Warrior::runaway(){
        if(owner){
            cout << name << " flees in terror, abandoning his lord, " << owner->getName() << endl;
            owner->warriorEscape(this);
        }else{
            cout << "I don't have an owner! I want one!" << endl;
        }
    }

    void Warrior::display() const{
            cout << "\t" << name << ": " << strength << endl;
    }
}


