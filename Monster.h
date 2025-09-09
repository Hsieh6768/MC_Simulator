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

	virtual void showInfo() const = 0;  // ��ʾ�����������
	virtual bool useSpecialAbility(int random_number) const = 0;  // �жϸûغ��Ƿ�ʹ����������
	virtual int dropMoney(int random_number) const = 0;  // ��������̱�ʯ

	std::string getType() const;  // ��ȡ���Ｖ��
	bool hasSpecialAbility() const;  // �ж��Ƿ�ӵ����������

private:
	std::string type;  // ����
	bool has_special_ability;  // �Ƿ�ӵ����������
	std::vector<std::string> special_ability;  // ���������б�
};

#endif
