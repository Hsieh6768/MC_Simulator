#include "EnderDragon.h"

EnderDragon::EnderDragon() : Monster("末影龙", health_max, health_max, attack, "史诗") {}

int EnderDragon::dropMoney(int random_number) const override {
    return DropConstants::ENDER_DRAGON_BASE_DROP + random_number % DropConstants::ENDER_DRAGON_DROP_RANGE;
}
