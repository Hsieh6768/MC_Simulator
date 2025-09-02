#include "Player.h"
#include <iostream>

Player::Player() {}

Player::Player(int hp_max, int hp_cur, int atk, int def, int mp_max, int mp_cur, int mon) : Creature(hp_max, hp_cur, atk), defense(def), magic_power_max(mp_max), magic_power_cur(mp_cur), money(mon) {}

Player::~Player() {}

void Player::showInfo() {
    std::cout << "HP: " << health_cur 
              << "\tATK: " << attack 
              << "\tDEF: " << defense 
              << "\tMP: " << magic_power_cur
              << "\tMONEY: " << money;
}

void Player::useSkill() {

}
