#include "Piglin.h"

Piglin::Piglin() : Monster("猪灵", health_max, health_max, attack, "普通", false, { "无" }) {}

void Piglin::showInfo() const {
    std::cout << "生命值：" << getHealthCur()
        << "\t攻击力：" << attack
        << "\n级别：" << getType()
        << "\t特殊能力：" << getAbility(0) << std::endl;
}

bool Piglin::useSpecialAbility(int random_number) const {
    return false;  // 无特殊能力
}

int Piglin::dropMoney(int random_number) const {
    // 绿宝石掉落值=基础掉落值+范围波动值
    return DropConstants::PIGLIN_BASE_DROP + random_number % DropConstants::PIGLIN_DROP_RANGE;
}
