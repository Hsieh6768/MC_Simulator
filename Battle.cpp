#include "Battle.h"
#include <iostream>
#include <thread>
#include <chrono>

Battle::Battle(Player& player, Monster& monster)
    : player(player), monster(monster) {
}

void Battle::start() {
    std::cout << "战斗开始! " << player.getName() << " vs " << monster.getName() << std::endl;

    while (!isBattleOver()) {
        // 玩家回合
        playerTurn();
        if (isBattleOver()) break;

        // 怪物回合
        monsterTurn();
    }

    // 战斗结果
    if (player.getHealthCur() <= 0) {
        std::cout << player.getName() << " 被击败了!" << std::endl;
    }
    else {
        std::cout << monster.getName() << " 被击败了!" << std::endl;
        // 玩家获得奖励
        int moneyEarned = monster.dropMoney(rand() % 100); // 随机掉落绿宝石
        player.setMoney(player.getMoney() + moneyEarned);
        std::cout << player.getName() << " 获得了 " << moneyEarned << " 绿宝石!" << std::endl;
    }
}

void Battle::playerTurn() {
    std::cout << "\n--- " << player.getName() << "的回合 ---" << std::endl;
    player.showInfo();
    std::cout << monster.getName() << " 生命值: " << monster.getHealthCur() << "/" << monster.getHealthMax() << std::endl;

    // 检查是否可以释放技能
    Skill playerSkill = player.getSkill();
    if (playerSkill.isReady() && player.getMagicPowerCur() >= playerSkill.getCost()) {
        std::cout << "是否使用技能 " << playerSkill.getName() << "? (y/n): ";
        char choice;
        std::cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            if (playerSkill.use(player)) {
                std::cout << "技能释放成功!" << std::endl;
            }
            else {
                std::cout << "技能释放失败!" << std::endl;
            }
        }
    }

    // 普通攻击
    applyPlayerAttack();

    // 减少技能冷却
    playerSkill.reduceCooldown();
}

void Battle::monsterTurn() {
    std::cout << "\n--- " << monster.getName() << "的回合 ---" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 短暂暂停

    applyMonsterAttack();
}

bool Battle::isBattleOver() const {
    return player.getHealthCur() <= 0 || monster.getHealthCur() <= 0;
}

void Battle::applyPlayerAttack() {
    int playerAttack = player.getAttack() + player.getEquipment().attack;
    int damage = std::max(1, playerAttack); // 至少造成1点伤害

    std::cout << player.getName() << " 对 " << monster.getName() << " 造成了 " << damage << " 点伤害!" << std::endl;
    monster.setHealthCur(monster.getHealthCur() - damage);
}

void Battle::applyMonsterAttack() {
    int monsterAttack = monster.getAttack();
    int playerDefense = player.getDefense() + player.getEquipment().defense;
    int damage = std::max(1, monsterAttack - playerDefense); // 至少造成1点伤害

    std::cout << monster.getName() << " 对 " << player.getName() << " 造成了 " << damage << " 点伤害!" << std::endl;
    player.setHealthCur(player.getHealthCur() - damage);
}