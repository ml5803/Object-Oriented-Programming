#ifndef PROTECTOR_H_INCLUDED
#define PROTECTOR_H_INCLUDED

#include <vector>
#include <string>
#include <iostream>

namespace WarriorCraft{
	class Noble;
	class Protector{
	public:
		Protector(const std::string& name, float str): name(name), strength(str){}
		const std::string& getName() const;
		Lord* getOwner() const;
		void setOwner(Lord* ptr);
		float getStr();
		void modifyStrength(float frac);
		void runaway();
		virtual void battlecry() const = 0;
		bool getAlive() const;
		void setAlive(bool status);
	private:
		std::string name;
		bool isAlive = true;
		float strength;
		Lord* owner = nullptr;
	};

	class Wizard: public Protector{
	public:
		Wizard(const std::string& name, float str):Protector(name,str){}
		void battlecry() const;
	};

	class Warrior: public Protector{
	public:
		Warrior(const std::string& name, float str): Protector(name,str){}
	};

	class Swordsman: public Warrior{
	public:
		Swordsman(const std::string& name,float str): Warrior(name,str){}
		void battlecry() const;
	};

	class Archer: public Warrior{
	public:
		Archer(const std::string& name, float str): Warrior(name,str){}
		void battlecry() const;
	};
}
#endif // PROTECTOR_H_INCLUDED
