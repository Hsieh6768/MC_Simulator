#include "Piglin.h"

Piglin::Piglin() : Monster("猪灵", health_max, health_max, attack, "普通", false) {}

void Piglin::showInfo() const {
    std::cout << "生命值：" << health_cur
              << "\t攻击力：" << attack
              << "\n级别：" << type
              << "\t特殊能力：" << "无" << std::endl;
}

bool Piglin::useSpecialAbility(int random_number) const {
    return false;
}

int Piglin::dropMoney(int random_number) const {
    return DropConstants::PIGLIN_BASE_DROP + random_number % DropConstants::PIGLIN_DROP_RANGE;
}
