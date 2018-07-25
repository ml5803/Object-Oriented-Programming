#ifndef NOBLE_H_INCLUDED
#define NOBLE_H_INCLUDED

#include <vector>
#include <string>
#include <iostream>

namespace WarriorCraft{
	class Protector;
	class Noble{
	public:
		Noble(const std::string& name) : name(name), isAlive(true){}
		void battle(Noble& enemy);
		virtual float getStr() const = 0;
		virtual void setStr(float frac) = 0;
		virtual void defend() const;
		bool getAlive() const;
		virtual void setAlive(bool status);
		const std::string& getName() const;
	private:
		std::string name;
		bool isAlive = true;
	};

	class PersonWithStrengthToFight : public Noble{
	public:
		PersonWithStrengthToFight(const std::string& name, float strength): Noble(name), strength(strength){}
		float getStr() const;
		void setStr(float frac);
	private:
		float strength;
	};

	class Lord: public Noble{
	public:
		Lord(const std::string& name): Noble(name){}
		float getStr() const;
		void setStr(float frac);
		void setAlive(bool status);
		void defend() const;
		void fire(Protector& protector);
		void hire(Protector& protector);
		void protectorEscape(Protector* protector);
	protected:
		float calcStrength() const;
	private:
		std::vector<Protector*> army;
		void pop_index(size_t index);
	};
}

#endif // NOBLE_H_INCLUDED
