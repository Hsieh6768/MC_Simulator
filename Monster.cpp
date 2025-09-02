#include "Monster.h"

Monster::Monster() {}

Monster::Monster(int hp_max, int hp_cur, int atk, int mon_drp) : Creature(hp_max, hp_cur, atk), money_dropped(mon_drp) {}

Monster::~Monster() {}
