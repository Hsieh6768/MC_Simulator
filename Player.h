#ifndef PLAYER_H
#define PLAYER_H
#include "Creature.h"

class Player : public Creature {
public:
	Player();
	Player(int hp_max, int hp_cur, int atk, int def, int mp_max, int mp_cur, int mon);
	~Player();
	void showInfo();
	void useSkill();

private:
	int defense;
	int magic_power_max;
	int magic_power_cur;
	int money;
};

#endif
