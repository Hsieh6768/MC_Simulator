#include "Piglin.h"

Piglin::Piglin() : Monster("����", health_max, health_max, attack, "��ͨ", false) {}

void Piglin::showInfo() const {
    std::cout << "����ֵ��" << health_cur
              << "\t��������" << attack
              << "\n����" << type
              << "\t����������" << "��" << std::endl;
}

bool Piglin::useSpecialAbility(int random_number) const {
    return false;
}

int Piglin::dropMoney(int random_number) const {
    return DropConstants::PIGLIN_BASE_DROP + random_number % DropConstants::PIGLIN_DROP_RANGE;
}
