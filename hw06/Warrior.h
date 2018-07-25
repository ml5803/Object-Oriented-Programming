#ifndef WARRIOR_H_INCLUDED
#define WARRIOR_H_INCLUDED

#include <vector>
#include <string>
#include <iostream>

namespace WarriorCraft{
    class Noble;
    class Warrior{
    public:
        friend std::ostream& operator<<(std::ostream& os,const Warrior& war);
        Warrior(const std::string& name, int str): name(name), strength(str), owner(nullptr), isAlive(true){}
        const std::string& getName() const;
        void setOwner(Noble* noble);
        bool getOwner() const;
        float getStrength() const;
        void modifyStrength(float fract);
        void runaway();
        void display() const;
    private:
        std::string name;
        float strength;
        Noble* owner;
        bool isAlive;
    };
}

#endif // WARRIOR_H_INCLUDED
