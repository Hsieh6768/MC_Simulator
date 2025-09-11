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

	virtual void showInfo() const = 0;  // 显示怪物属性面板
	virtual bool useSpecialAbility(int random_number) const = 0;  // 判断该回合是否使用特殊能力
	virtual int dropMoney(int random_number) const = 0;  // 随机掉落绿宝石

	std::string getType() const;  // 获取怪物级别
	bool hasSpecialAbility() const;  // 判断是否拥有特殊能力
	std::string getAbility(int index = 0) const;  // 获取怪物特殊能力

private:
	std::string type;  // 级别
	bool has_special_ability;  // 是否拥有特殊能力
	std::vector<std::string> special_ability;  // 特殊能力列表
};

#endif
