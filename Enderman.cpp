#include "Enderman.h"

Enderman::Enderman() : Monster("�ս�ʹ��", health_max, health_max, attack, "��Ӣ", true, { "˲���ƶ�" }) {}

void Enderman::showInfo() const {
    std::cout << "����ֵ��" << health_cur
        << "\t��������" << attack
        << "\n����" << type
        << "\t����������1��" << special_ability[0] << std::endl;
}

bool Enderman::useSpecialAbility(int random_number) const {
    // ����Ϊ1ʱ�ڱ��غ�ʹ����������
    return random_number % SpecialAbilityConstants::ENDERMAN_N == 1;
}

int Enderman::dropMoney(int random_number) const {
    // �̱�ʯ����ֵ=��������ֵ+��Χ����ֵ
    return DropConstants::ENDERMAN_BASE_DROP + random_number % DropConstants::ENDERMAN_DROP_RANGE;
}
