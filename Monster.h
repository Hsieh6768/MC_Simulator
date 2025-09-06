#ifndef MONSTER_H
#define MONSTER_H
#include "Creature.h"
#include "MonsterConstants.h"

class Monster : public Creature {
public:
	Monster(
		std::string name = "",
		int health_max = 0,
		int health_cur = 0,
		int attack = 0,
		std::string type = "", 
		bool has_special_ability = false
	);
	~Monster() {}

	virtual void showInfo() const = 0;
	virtual bool useSpecialAbility(int random_number) const = 0;
	bool hasSpecialAbility() const;
	virtual int dropMoney(int random_number) const = 0;  // 随机掉落绿宝石

private:
	std::string type;
	bool has_special_ability;
};

#endif
