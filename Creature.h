#ifndef CREATURE_H
#define CREATURE_H

class Creature {
public:
	Creature();  // default constructor
	Creature(int hp_max, int hp_cur, int atk);  // constructor
	~Creature();

private:
	int health_max;
	int health_cur;
	int attack;
};

#endif
