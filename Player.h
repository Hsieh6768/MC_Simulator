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

	void showInfo() const;  // �鿴�������
	int getDefense() const;  // ��ȡ��һ���ֵ
	void setDefense(int defense);  // �趨��һ���ֵ
	int getMagicPowerMax() const;  // ��ȡ������ħ��ֵ
	void setMagicPowerMax(int magic_power_max);  // �趨������ħ��ֵ
	int getMagicPowerCur() const;  // ��ȡ��ǰħ��ֵ
	void setMagicPowerCur(int magic_power_cur);  // �趨��ǰħ��ֵ
	int getMoney() const;  // ��ȡ����̱�ʯ����
	void setMoney(int money);  // �趨����̱�ʯ����
	Equipment getEquipment() const;  // ��ȡ��һ���
	void setEquipment(const Equipment &equipment);  // �趨��һ���
	Skill getSkill() const;  // ��ȡ��Ҽ���
	void setSkill(const Skill &skill);  // �趨��Ҽ���
	void useSkill(std::string skill);

private:
	int defense;  // ��һ���ֵ
	int magic_power_max;  // ������ħ��ֵ
	int magic_power_cur;  // ������ħ��ֵ
	int money;  // ����̱�ʯ����
	Equipment equipment;
	Skill skill;
};

#endif
