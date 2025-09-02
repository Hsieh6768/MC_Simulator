#include "Creature.h"

Creature::Creature() {}

Creature::Creature(int hp_max, int hp_cur, int atk) : health_max(hp_cur), health_cur(hp_cur), attack(atk) {}

Creature::~Creature() {}
