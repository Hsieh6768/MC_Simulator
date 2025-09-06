#include "Enderman.h"

Enderman::Enderman() : Monster("终界使者", health_max, health_max, attack, "精英") {}

void Enderman::showInfo() const {
    std::cout << "生命值：" << health_cur
              << "\t攻击力：" << attack
              << "\n级别：" << type
              << "\t特殊能力：" << "瞬间移动" << std::endl;
}

bool Enderman::useSpecialAbility(int random_number) const {
    return random_number % SpecialAbilityConstants::ENDERMAN_N == 1;
}

int Enderman::dropMoney(int random_number) const {
    return DropConstants::ENDERMAN_BASE_DROP + random_number % DropConstants::ENDERMAN_DROP_RANGE;
}
