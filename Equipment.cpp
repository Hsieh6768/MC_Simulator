#include "Equipment.h"
#include <iostream>

using namespace std;

Equipment::Equipment(string name, int atk, int def, int value, string type)
    : name(name), attack(atk), defense(def), value(value), type(type) {}

void Equipment::displayInfo() const {
    cout << "װ��: " << name << " [" << type << "]" << endl;
    if (attack > 0) {
        cout << "����: +" << attack << endl;
    }
    if (defense > 0) {
        cout << "����: +" << defense << endl;
    }
    cout << "��ֵ: " << value << " �̱�ʯ" << endl;
}

int Equipment::getValue() const {
    return value;
}

void Equipment::upgrade(int atkBonus, int defBonus) {
    attack += atkBonus;
    defense += defBonus;
    value += (atkBonus + defBonus) * 5; // ��ֵ����
}

string Equipment::getType() const {
    return type;
}

bool Equipment::operator<(const Equipment& other) const {
    // ����ֵ����
    return value < other.value;
}

// Ԥ����װ��ʵ��
namespace EquipmentTypes {
    // ����
    const Equipment WOODEN_SWORD("ľ��", 3, 0, 10, "weapon");
    const Equipment IRON_SWORD("����", 8, 1, 40, "weapon");
    const Equipment DIAMOND_SWORD("��ʯ��", 12, 2, 80, "weapon");

    // ����
    const Equipment LEATHER_ARMOR("Ƥ���", 0, 3, 15, "armor");
    const Equipment IRON_ARMOR("����", 0, 6, 35, "armor");
    const Equipment DIAMOND_ARMOR("��ʯ��", 0, 10, 70, "armor");
}