#include "EnderDragon.h"

EnderDragon::EnderDragon() : Monster("终界龙", health_max, health_max, attack, "史诗", true) {}

void EnderDragon::showInfo() const {
    std::cout << "生命值：" << health_cur
              << "\t攻击力：" << attack
              << "\n级别：" << type
              << "\t特殊能力：" << "冲撞攻击；龙息腐蚀" << std::endl;
}

bool EnderDragon::useSpecialAbility(int random_number) const {
    return random_number % SpecialAbilityConstants::ENDER_DRAGON_N == 1;
}

int EnderDragon::dropMoney(int random_number) const {
    return DropConstants::ENDER_DRAGON_BASE_DROP + random_number % DropConstants::ENDER_DRAGON_DROP_RANGE;
}
