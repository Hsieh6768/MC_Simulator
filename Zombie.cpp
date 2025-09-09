#include "Zombie.h"

Zombie::Zombie() : Monster("��ʬ", health_max, health_max, attack, "��ͨ", false, { "��" }) {}

void Zombie::showInfo() const {
    std::cout << "����ֵ��" << health_cur
        << "\t��������" << attack
        << "\n����" << type
        << "\t����������" << special_ability[0] << std::endl;
}

bool Zombie::useSpecialAbility(int random_number) const {
    return false;  // ����������
}

int Zombie::dropMoney(int random_number) const {
    // �̱�ʯ����ֵ=��������ֵ+��Χ����ֵ
    return DropConstants::ZOMBIE_BASE_DROP + random_number % DropConstants::ZOMBIE_DROP_RANGE;
}
