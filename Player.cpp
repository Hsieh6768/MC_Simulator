#include "Player.h"
#include <iostream>

Player::Player(
    std::string name, 
    int health_max, 
    int health_cur, 
    int attack, 
    int defense, 
    int magic_power_max, 
    int magic_power_cur, 
    int money, 
    Equipment equipment, 
    Skill skill
) : Creature(name, health_max, health_cur, attack), 
    defense(defense), 
    magic_power_max(magic_power_max), 
    magic_power_cur(magic_power_cur), 
    money(money), 
    equipment(equipment), 
    skill(skill) {}

Player::~Player() {}

void Player::showInfo() const {
    std::cout << "生命值：" << health_cur 
              << "\t攻击力：" << attack + equipment.attack
              << "\t防御力" << defense + equipment.defense
              << "\n魔力：" << magic_power_cur
              << "\t绿宝石：" << money << std::endl;
}

int Player::getDefense() const {
    return this->defense;
}

void Player::setDefense(int defense) {
    this->defense = defense;
}

int Player::getMagicPowerMax() const {
    return this->magic_power_max;
}

void Player::setMagicPowerMax(int magic_power_max) {
    this->magic_power_max = magic_power_max;
}

int Player::getMagicPowerCur() const {
    return this->magic_power_cur;
}

void Player::setMagicPowerCur(int magic_power_cur) {
    this->magic_power_cur = magic_power_cur;
}

int Player::getMoney() const {
    return this->money;
}

void Player::setMoney(int money) {
    this->money = money;
}

Equipment Player::getEquipment() const {
    return this->equipment.name;
}

void Player::setEquipment(const Equipment &equipment) {
    this->equipment.name = equipment.name;
}

Skill Player::getSkill() const {
    return this->skill.name;
}

void Player::setSkill(const Skill &skill) {
    this->skill.name = skill.name;
}

void Player::useSkill() {

}
