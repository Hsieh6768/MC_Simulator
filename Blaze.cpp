#include "Blaze.h"

Blaze::Blaze() : Monster("����ʹ��", health_max, health_max, attack, "��Ӣ", true, {"���򹥻�"}) {}

void Blaze::showInfo() const {
    std::cout << "����ֵ��" << health_cur
              << "\t��������" << attack
              << "\n����" << type
              << "\t����������1��" << special_ability[0] << std::endl;
}

bool Blaze::useSpecialAbility(int random_number) const {
    return random_number % SpecialAbilityConstants::BLAZE_N == 1;
}

int Blaze::dropMoney(int random_number) const {
    return DropConstants::BLAZE_BASE_DROP + random_number % DropConstants::BLAZE_DROP_RANGE;
}
