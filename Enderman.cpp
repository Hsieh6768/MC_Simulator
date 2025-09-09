#include "Enderman.h"

Enderman::Enderman() : Monster("终界使者", health_max, health_max, attack, "精英", true, { "瞬间移动" }) {}

void Enderman::showInfo() const {
    std::cout << "生命值：" << health_cur
        << "\t攻击力：" << attack
        << "\n级别：" << type
        << "\t特殊能力：1、" << special_ability[0] << std::endl;
}

bool Enderman::useSpecialAbility(int random_number) const {
    // 余数为1时在本回合使用特殊能力
    return random_number % SpecialAbilityConstants::ENDERMAN_N == 1;
}

int Enderman::dropMoney(int random_number) const {
    // 绿宝石掉落值=基础掉落值+范围波动值
    return DropConstants::ENDERMAN_BASE_DROP + random_number % DropConstants::ENDERMAN_DROP_RANGE;
}
