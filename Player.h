#ifndef PLAYER_H
#define PLAYER_H
#include "Creature.h"
#include "Equipment.h"
#include "Skill.h"

class Player : public Creature {
public:
	Player(
		std::string name = "", 
		int health_max = 0, 
		int health_cur = 0, 
		int attack = 0, 
		int defense = 0, 
		int magic_power_max = 0, 
		int magic_power_cur = 0, 
		int money = 0, 
		Equipment equipment = Equipment(), 
		Skill skill = Skill()
	);
	~Player();

	void showInfo() const;  // 查看玩家属性
	int getDefense() const;  // 获取玩家护甲值
	void setDefense(int defense);  // 设定玩家护甲值
	int getMagicPowerMax() const;  // 获取玩家最大魔力值
	void setMagicPowerMax(int magic_power_max);  // 设定玩家最大魔力值
	int getMagicPowerCur() const;  // 获取当前魔力值
	void setMagicPowerCur(int magic_power_cur);  // 设定当前魔力值
	int getMoney() const;  // 获取玩家绿宝石数量
	void setMoney(int money);  // 设定玩家绿宝石数量
	Equipment getEquipment() const;  // 获取玩家护甲
	void setEquipment(const Equipment &equipment);  // 设定玩家护甲
	Skill getSkill() const;  // 获取玩家技能
	void setSkill(const Skill &skill);  // 设定玩家技能
	void useSkill(std::string skill);

private:
	int defense;  // 玩家护甲值
	int magic_power_max;  // 玩家最大魔力值
	int magic_power_cur;  // 玩家最大魔力值
	int money;  // 玩家绿宝石数量
	Equipment equipment;
	Skill skill;
};

#endif
