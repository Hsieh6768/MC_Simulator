#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <string>

class Equipment {
public:
    std::string name;
    int attack;
    int defense;
    int value;  // װ����ֵ
    std::string type; // װ�����ͣ�weapon, armor, accessory

    // ���캯��
    Equipment(std::string name = "��װ��", int atk = 0, int def = 0,
        int value = 0, std::string type = "weapon");

    // ��ʾװ����Ϣ
    void displayInfo() const;

    // ��ȡװ����ֵ
    int getValue() const;

    // װ������
    void upgrade(int atkBonus = 0, int defBonus = 0);

    // ��ȡװ������
    std::string getType() const;

    // �Ƚ�װ������������
    bool operator<(const Equipment& other) const;
};

// Ԥ����װ������
namespace EquipmentTypes {
    // ����
    extern const Equipment WOODEN_SWORD;
    extern const Equipment STONE_SWORD;
    extern const Equipment IRON_SWORD;
    extern const Equipment DIAMOND_SWORD;
    extern const Equipment FIRE_SWORD;
    extern const Equipment ICE_SWORD;

    // ����
    extern const Equipment LEATHER_ARMOR;
    extern const Equipment IRON_ARMOR;
    extern const Equipment DIAMOND_ARMOR;
    extern const Equipment FIRE_ARMOR;
    extern const Equipment ICE_ARMOR;

    // ��Ʒ
    extern const Equipment HEALTH_RING;
    extern const Equipment MANA_RING;
    extern const Equipment LUCKY_CHARM;
}

#endif // EQUIPMENT_H