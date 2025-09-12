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
    Weapon weapon,
    Armor armor,
    std::vector<std::unique_ptr<Skill>> skill,
    struct TemporaryBuff buff
) : Creature(name, health_max, health_cur, attack),
defense(defense),
magic_power_max(magic_power_max),
magic_power_cur(magic_power_cur),
money(money),
weapon(weapon),
armor(armor),
skill(std::move(skill)),
buff(buff) {}

Player::~Player() {}

Player::Player(Player&& other) noexcept
    : Creature(std::move(other)),
    defense(other.defense),
    magic_power_max(other.magic_power_max),
    magic_power_cur(other.magic_power_cur),
    money(other.money),
    weapon(std::move(other.weapon)),
    armor(std::move(other.armor)),
    skill(std::move(other.skill)),
    buff(other.buff) {
}

Player& Player::operator=(Player&& other) noexcept {
    if (this != &other) {
        Creature::operator=(std::move(other));
        defense = other.defense;
        magic_power_max = other.magic_power_max;
        magic_power_cur = other.magic_power_cur;
        money = other.money;
        weapon = std::move(other.weapon);
        armor = std::move(other.armor);
        skill = std::move(other.skill);
        buff = other.buff;
    }
    return *this;
}

void Player::showInfo() const {
    std::cout << "生命值: " << getHealthCur()
              << "\t攻击力: " << getAttack() << " + " <<  weapon.getAttack() << " + " << buff.attack_bonus
              << "\t护甲值: " << defense << " + " << armor.getDefense() << " + " << buff.defense_bonus
              << "\t魔力值: " << magic_power_cur << " (每三回合回复一点)"
              << "\t绿宝石: " << money << std::endl;
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

const Weapon& Player::getWeapon() const {
    return this->weapon;
}

void Player::setWeapon(const Weapon& weapon) {
    this->weapon = weapon;
}

const Armor& Player::getArmor() const {
    return this->armor;
}

void Player::setArmor(const Armor& armor) {
    this->armor = armor;
}

std::vector<std::unique_ptr<Skill>>& Player::getSkill() {
    return this->skill;
}

const std::vector<std::unique_ptr<Skill>>& Player::getSkill() const {
    return this->skill;
}

void Player::addSkill(std::unique_ptr<Skill> skill) {
    this->skill.push_back(std::move(skill));
}

void Player::clearSkills() {
    this->skill.clear();
}

TemporaryBuff Player::getTemporaryBuff() const {
    return this->buff;
}

void Player::setTemporaryBuff(const TemporaryBuff buff) {
    this->buff = buff;
}

void Player::updateBuffs() {
    if (buff.duration > 0) {
        buff.duration--;
        if (buff.duration == 0) {  // 增益持续时间结束
            buff.attack_bonus = 0;
            buff.defense_bonus = 0;
        }
    }
}
