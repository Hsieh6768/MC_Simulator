#include "Equipment.h"
#include <iostream>

using namespace std;

Equipment::Equipment(string name, int atk, int def, int value, string type)
    : name(name), attack(atk), defense(def), value(value), type(type) {}

void Equipment::displayInfo() const {
    cout << "装备: " << name << " [" << type << "]" << endl;
    if (attack > 0) {
        cout << "攻击: +" << attack << endl;
    }
    if (defense > 0) {
        cout << "防御: +" << defense << endl;
    }
    cout << "价值: " << value << " 绿宝石" << endl;
}

int Equipment::getValue() const {
    return value;
}

void Equipment::upgrade(int atkBonus, int defBonus) {
    attack += atkBonus;
    defense += defBonus;
    value += (atkBonus + defBonus) * 5; // 价值提升
}

string Equipment::getType() const {
    return type;
}

bool Equipment::operator<(const Equipment& other) const {
    // 按价值排序
    return value < other.value;
}

// 预定义装备实现
namespace EquipmentTypes {
    // 武器
    const Equipment WOODEN_SWORD("木剑", 3, 0, 10, "weapon");
    const Equipment IRON_SWORD("铁剑", 8, 1, 40, "weapon");
    const Equipment DIAMOND_SWORD("钻石剑", 12, 2, 80, "weapon");

    // 防具
    const Equipment LEATHER_ARMOR("皮革甲", 0, 3, 15, "armor");
    const Equipment IRON_ARMOR("铁甲", 0, 6, 35, "armor");
    const Equipment DIAMOND_ARMOR("钻石甲", 0, 10, 70, "armor");
}