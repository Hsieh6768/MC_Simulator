#include "Zombie.h"

Zombie::Zombie() : Monster("僵尸", health_max, health_max, attack, "普通", 
    "常见的亡灵生物，在黑暗中生成并会召唤更多同伴。", false, {"无"}) {}

void Zombie::showInfo() const {
    std::cout << "生命值: " << getHealthCur()
              << "\t攻击力: " << attack
              << "\t级别: " << getType()
              << "\n特点: " << getDescription()
              << "\n特殊能力: " << getAbility(0) << std::endl;
}

bool Zombie::useSpecialAbility(int random_number) const {
    return false;  // 无特殊能力
}

int Zombie::dropMoney(int random_number) const {
    // 绿宝石掉落值=基础掉落值+范围波动值
    return DropConstants::ZOMBIE_BASE_DROP + random_number % DropConstants::ZOMBIE_DROP_RANGE;
}
