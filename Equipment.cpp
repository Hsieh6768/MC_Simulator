#include "Equipment.h"

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

std::string Equipment::getName() const {
    return name;
}

int Equipment::getAttack() const {
    return attack;
}

int Equipment::getDefense() const {
    return defense;
}

int Equipment::getValue() const {
    return value;
}

string Equipment::getType() const {
    return type;
}

bool Equipment::operator<(const Equipment& other) const {
    // 按价值排序
    return value < other.value;
}

// Weapon 实现
Weapon::Weapon(string name, int atk, int value)
    : Equipment(name, atk, 0, value, "weapon") {}

void Weapon::displayInfo() const {
    cout << "武器: " << getName() << endl;
    cout << "攻击: +" << getAttack() << endl;
    cout << "价值: " << getValue() << " 绿宝石" << endl;
}

// Armor 实现
Armor::Armor(string name, int def, int value)
    : Equipment(name, 0, def, value, "armor") {}

void Armor::displayInfo() const {
    cout << "护甲: " << getName() << endl;
    cout << "防御: +" << getDefense() << endl;
    cout << "价值: " << getValue() << " 绿宝石" << endl;
}

// 预定义装备实现
namespace EquipmentTypes {
    // 武器
    const Weapon WOODEN_SWORD("木剑", 5, 10);
    const Weapon IRON_SWORD("铁剑", 9, 40);
    const Weapon DIAMOND_SWORD("钻石剑", 15, 80);

    // 防具
    const Armor LEATHER_ARMOR("皮革甲", 2, 15);
    const Armor IRON_ARMOR("铁甲", 6, 35);
    const Armor DIAMOND_ARMOR("钻石甲", 12, 70);
}