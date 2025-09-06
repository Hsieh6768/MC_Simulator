#ifndef CREATURE_H
#define CREATURE_H
#include <string>

class Creature {
public:
	Creature(
		std::string name = "", 
		int health_max = 0, 
		int health_cur = 0, 
		int attack = 0
	);
	~Creature();

	std::string getName() const;
	void setName(std::string name);
	int getHealthMax() const;
	void setHealthMax(int health_max);
	int getHealthCur() const;
	void setHealthCur(int health_cur);
	int getAttack() const;
	void setAttack(int attack);

private:
	std::string name;
	int health_max;
	int health_cur;
	int attack;
};

#endif
