#ifndef CREATURE_H
#define CREATURE_H
#include <iostream>
#include <string>

class Creature {
public:
	Creature(
		std::string name = "",
		int health_max = 0,
		int health_cur = 0,
		int attack = 0
	);
	virtual ~Creature();

	std::string getName() const;  // ��ȡ��������
	void setName(std::string name);  // �趨��������
	int getHealthMax() const;  // ��ȡ�������ֵ
	void setHealthMax(int health_max);  // �趨�������ֵ
	int getHealthCur() const;  // ��ȡ��ǰ����ֵ
	void setHealthCur(int health_cur);  // �趨��ǰ����ֵ
	int getAttack() const;  // ��ȡ������
	void setAttack(int attack);  // �趨������

private:
	std::string name;  // ��������
	int health_max;  // �������ֵ
	int health_cur;  // ��ǰ����ֵ
	int attack;  // ������
};

#endif
