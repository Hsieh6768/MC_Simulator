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

	std::string getName() const;  // 获取生物名称
	void setName(std::string name);  // 设定生物名称

	int getHealthMax() const;  // 获取最大生命值
	void setHealthMax(int health_max);  // 设定最大生命值

	int getHealthCur() const;  // 获取当前生命值
	void setHealthCur(int health_cur);  // 设定当前生命值

	int getAttack() const;  // 获取攻击力
	void setAttack(int attack);  // 设定攻击力

private:
	std::string name;  // 生物名称
	int health_max;  // 最大生命值
	int health_cur;  // 当前生命值
	int attack;  // 攻击力
};

#endif
