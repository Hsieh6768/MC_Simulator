#ifndef MONSTER_H
#define MONSTER_H

#include "Creature.h"
#include "MonsterConstants.h"
#include "ColorManager.h"
#include <vector>

struct MonsterBuff {  // 怪物增益状态
	int attack_bonus;
	int duration;
	bool activated;  // 增益是否已触发
	bool dodged;  // 怪物下回合是否闪避
};

class Monster : public Creature {
public:
	Monster(
		std::string name = "",
		int health_max = 0,
		int health_cur = 0,
		int attack = 0,
		std::string type = "",
		std::string description = "",
		MonsterBuff buff = { 0, 0, false, false },
		bool has_special_ability = false,
		std::vector<std::string> special_ability = {}, 
		std::vector<std::string> special_ability_description = {}
	);
	virtual ~Monster() = default;

	virtual void showInfo() const = 0;  // 显示怪物属性面板
	virtual bool useSpecialAbility(int random_number) const = 0;  // 判断该回合是否使用特殊能力
	virtual int dropMoney(int random_number) const = 0;  // 随机掉落绿宝石

	std::string getType() const;  // 获取怪物级别
	std::string getDescription() const;  // 获取怪物描述

	MonsterBuff getMonsterBuff() const;  // 获取怪物增益
	void setMonsterBuff(const MonsterBuff buff);  // 设定怪物增益
	void updateMonsterBuffs();  // 更新怪物增益状态

	bool hasSpecialAbility() const;  // 判断是否拥有特殊能力
	std::string getAbility(int index = 0) const;  // 获取怪物特殊能力
	std::string getAbilityDescription(int index = 0) const;  // 获取怪物特殊能力描述

private:
	std::string type;  // 级别
	std::string description;  // 怪物描述
	MonsterBuff buff;  // 怪物增益效果
	bool has_special_ability;  // 是否拥有特殊能力
	std::vector<std::string> special_ability;  // 特殊能力列表
	std::vector<std::string> special_ability_description;  // 特殊能力描述
};

#endif
