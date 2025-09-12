#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"
#include "Equipment.h"
#include "Skill.h"
#include <vector>
#include <memory>

struct TemporaryBuff {
	int attack_bonus;
	int defense_bonus;
	int duration;
};

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
		Weapon weapon = Weapon(), 
		Armor armor = Armor(), 
		std::vector<std::unique_ptr<Skill>> skill = {},
		TemporaryBuff buff = {0, 0, 0}
	);
	~Player();

	Player(Player&& other) noexcept;  // 添加移动构造函数
	Player& operator=(Player&& other) noexcept;  // 添加移动赋值运算符
	Player(const Player&) = delete;  // 删除拷贝构造函数
	Player& operator=(const Player&) = delete;  // 删除拷贝赋值运算符

	void showInfo() const;  // 查看玩家属性

	int getDefense() const;  // 获取玩家护甲值
	void setDefense(int defense);  // 设定玩家护甲值

	int getMagicPowerMax() const;  // 获取玩家最大魔力值
	void setMagicPowerMax(int magic_power_max);  // 设定玩家最大魔力值

	int getMagicPowerCur() const;  // 获取当前魔力值
	void setMagicPowerCur(int magic_power_cur);  // 设定当前魔力值

	int getMoney() const;  // 获取玩家绿宝石数量
	void setMoney(int money);  // 设定玩家绿宝石数量

	const Weapon& getWeapon() const;  // 获取玩家武器
	void setWeapon(const Weapon& weapon);  // 设定玩家武器

	const Armor& getArmor() const;  // 获取玩家护甲
	void setArmor(const Armor& armor);  // 设定玩家护甲

	std::vector<std::unique_ptr<Skill>>& getSkill();  // 获取玩家技能（可修改引用）
	const std::vector<std::unique_ptr<Skill>>& getSkill() const;  // 获取玩家技能（只读引用）
	void addSkill(std::unique_ptr<Skill> skill);  // 添加玩家技能
	void clearSkills();  // 清除玩家技能

	TemporaryBuff getTemporaryBuff() const;  // 获取玩家增益
	void setTemporaryBuff(const TemporaryBuff buff);  // 设定玩家增益
	void updateBuffs();  // 更新玩家增益状态

private:
	int defense;  // 玩家护甲值
	int magic_power_max;  // 玩家最大魔力值
	int magic_power_cur;  // 玩家最大魔力值
	int money;  // 玩家绿宝石数量
	Weapon weapon;  // 玩家佩戴的武器
	Armor armor;  // 玩家穿戴的护甲
	std::vector<std::unique_ptr<Skill>> skill;  // 玩家拥有的技能
	TemporaryBuff buff;  // 玩家短时增益
};

#endif
