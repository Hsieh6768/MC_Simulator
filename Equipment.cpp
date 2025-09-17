#include "Equipment.h"

using namespace std;

Equipment::Equipment(string name, int atk, int def, int value, string type)
    : name(name), attack(atk), defense(def), value(value), type(type) {}

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
    ColorManager::COLOR_PRINT("武器: ", YELLOW);
    ColorManager::COLOR_PRINT(getName(), YELLOW);

    ColorManager::COLOR_PRINT("\t攻击: +", YELLOW);
    cout << getAttack();

    ColorManager::COLOR_PRINT("\t价值: ", YELLOW);
    cout << getValue();

    ColorManager::COLOR_PRINT(" 绿宝石\n", YELLOW);
}

// Armor 实现
Armor::Armor(string name, int def, int value)
    : Equipment(name, 0, def, value, "armor") {}

void Armor::displayInfo() const {
    ColorManager::COLOR_PRINT("护甲: ", YELLOW);
    ColorManager::COLOR_PRINT(getName(), YELLOW);

    ColorManager::COLOR_PRINT("\t防御: +", YELLOW);
    cout << getDefense();

    ColorManager::COLOR_PRINT("\t价值: ", YELLOW);
    cout << getValue();

    ColorManager::COLOR_PRINT(" 绿宝石\n", YELLOW);
}

// 预定义装备实现
namespace EquipmentTypes {
    // 武器
    const Weapon WOODEN_SWORD("木剑", 5, 5);
    const Weapon IRON_SWORD("铁剑", 9, 20);
    const Weapon DIAMOND_SWORD("钻石剑", 15, 40);

    // 防具
    const Armor LEATHER_ARMOR("皮革甲", 2, 8);
    const Armor IRON_ARMOR("铁甲", 6, 18);
    const Armor DIAMOND_ARMOR("钻石甲", 12, 35);
}