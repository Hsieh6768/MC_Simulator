#include "Zombie.h"

Zombie::Zombie() : Monster("僵尸", health_max, health_max, attack, "普通") {}

int Zombie::dropMoney(int random_number) const override {
    return DropConstants::ZOMBIE_BASE_DROP + random_number % DropConstants::ZOMBIE_DROP_RANGE;
}
