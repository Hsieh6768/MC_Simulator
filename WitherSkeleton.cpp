#include "WitherSkeleton.h"

WitherSkeleton::WitherSkeleton() : Monster("��������", health_max, health_max, attack, "��ͨ", true) {}

void WitherSkeleton::showInfo() const {
    std::cout << "����ֵ��" << health_cur
              << "\t��������" << attack
              << "\n����" << type
              << "\t����������" << "��������" << std::endl;
}

bool WitherSkeleton::useSpecialAbility(int random_number) const {
    return random_number % SpecialAbilityConstants::WITHER_SKELETON_N == 1;
}

int WitherSkeleton::dropMoney(int random_number) const {
    return DropConstants::WITHER_SKELETON_BASE_DROP + random_number % DropConstants::WITHER_SKELETON_DROP_RANGE;
}
