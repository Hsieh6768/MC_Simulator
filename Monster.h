#ifndef MONSTER_H
#define MONSTER_H
#include "Creature.h"
#include "MonsterConstants.h"
#include <vector>

class Monster : public Creature {
public:
	Monster(
		std::string name = "",
		int health_max = 0,
		int health_cur = 0,
		int attack = 0,
		std::string type = "",
		bool has_special_ability = false,
		std::vector<std::string> special_ability = {}
	);
	~Monster() {}

	virtual void showInfo() const = 0;
	virtual bool useSpecialAbility(int random_number) const = 0;
	virtual int dropMoney(int random_number) const = 0;  // Ëæ»úµôÂäÂÌ±¦Ê¯

	std::string getType() const;
	bool hasSpecialAbility() const;

private:
	std::string type;
	bool has_special_ability;
	std::vector<std::string> special_ability;
};

#endif
