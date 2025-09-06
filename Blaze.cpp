#include "Blaze.h"

Blaze::Blaze() : Monster("烈焰使者", health_max, health_max, attack, "精英", true, {"火球攻击"}) {}

void Blaze::showInfo() const {
    std::cout << "生命值：" << health_cur
              << "\t攻击力：" << attack
              << "\n级别：" << type
              << "\t特殊能力：1、" << special_ability[0] << std::endl;
}

bool Blaze::useSpecialAbility(int random_number) const {
    return random_number % SpecialAbilityConstants::BLAZE_N == 1;
}

int Blaze::dropMoney(int random_number) const {
    return DropConstants::BLAZE_BASE_DROP + random_number % DropConstants::BLAZE_DROP_RANGE;
}
