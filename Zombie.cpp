#include "Zombie.h"

Zombie::Zombie() : Monster("僵尸", health_max, health_max, attack, "普通", false, { "无" }) {}

void Zombie::showInfo() const {
    std::cout << "生命值：" << getHealthCur()
        << "\t攻击力：" << attack
        << "\n级别：" << getType()
        << "\t特殊能力：" << getAbility(0) << std::endl;
}

bool Zombie::useSpecialAbility(int random_number) const {
    return false;  // 无特殊能力
}

int Zombie::dropMoney(int random_number) const {
    // 绿宝石掉落值=基础掉落值+范围波动值
    return DropConstants::ZOMBIE_BASE_DROP + random_number % DropConstants::ZOMBIE_DROP_RANGE;
}
