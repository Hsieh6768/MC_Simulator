#include "Zombie.h"

Zombie::Zombie() : Monster("僵尸", health_max, health_max, attack, "普通") {}

void Zombie::showInfo() const {
    std::cout << "生命值：" << health_cur
              << "\t攻击力：" << attack
              << "\n级别：" << type
              << "\t特殊能力：" << "无" << std::endl;
}

bool Zombie::useSpecialAbility(int random_number) const {
    return false;
}

int Zombie::dropMoney(int random_number) const {
    return DropConstants::ZOMBIE_BASE_DROP + random_number % DropConstants::ZOMBIE_DROP_RANGE;
}
