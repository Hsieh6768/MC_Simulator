#ifndef MONSTER_H
#define MONSTER_H
#include "Creature.h"

class Monster : public Creature {
public:
	Monster();
	Monster(int hp_max, int hp_cur, int atk, int mon);
	~Monster() {}
	virtual int dropMoney(int random_number) const = 0;  // need a rand() function to produce and pass random numbers

private:
	int money_dropped;
};

#endif
