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

	void showInfo() const;
	int getDefense() const;
	void setDefense(int defense);
	int getMagicPowerMax() const;
	void setMagicPowerMax(int magic_power_max);
	int getMagicPowerCur() const;
	void setMagicPowerCur(int magic_power_cur);
	int getMoney() const;
	void setMoney(int money);
	Equipment getEquipment() const;
	void setEquipment(const Equipment &equipment);
	Skill getSkill() const;
	void setSkill(const Skill &skill);
	void useSkill();

private:
	int defense;
	int magic_power_max;
	int magic_power_cur;
	int money;
	Equipment equipment;
	Skill skill;
};

#endif
