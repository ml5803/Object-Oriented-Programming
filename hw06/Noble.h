#ifndef NOBLE_H_INCLUDED
#define NOBLE_H_INCLUDED

#include <vector>
#include <string>
#include <iostream>

namespace WarriorCraft{
    class Warrior;
    class Noble{
    public:
        friend std::ostream& operator<<(std::ostream& os,const Noble& noble);
        Noble(const std::string& name) : name(name), isAlive(true){}
        const std::string& getName() const;
        void hire(Warrior& warrior);
        void fire(Warrior& warrior);
        void warriorEscape(Warrior* warrior);
        float calcStrength() const;
        void battle(Noble& enemy);
        void display() const;
    private:
        std::string name;
        std::vector<Warrior*> army;
        bool isAlive;
        void pop_index(size_t index);
    };
}

#endif // NOBLE_H_INCLUDED
