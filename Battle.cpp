#include "Battle.h"
#include <iostream>
#include <algorithm>
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
        if (isBattleOver()) 
            break;

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
    // 回合开始处理
    player.updateBuffs();
    std::vector<std::unique_ptr<Skill>>& skills = player.getSkill();
    for (auto& skill : skills) {
        skill->reduceCooldown();
    }
    
    std::cout << "\n--- " << player.getName() << " 的回合 ---" << std::endl;
    player.showInfo();
    std::cout << monster.getName() << " 生命值: " << monster.getHealthCur() << "/" << monster.getHealthMax() << std::endl;

    int choice;
    bool validChoice = false;

    while (!validChoice) {
        std::cout << "0. 普通攻击" << std::endl;

        // 显示所有技能及其状态
        std::cout << "\n技能列表:" << std::endl;
        int index = 0;
        for (auto& skill : skills) {
            std::cout << index + 1 << ". " << skill->getName();

            if (!skill->isReady()) {
                std::cout << " (冷却中: " << skill->getCurrentCooldown() << "回合)";
            }
            else if (player.getMagicPowerCur() < skill->getCost()) {
                std::cout << " (魔法不足)";
            }
            else if (skill->getName() == "力量强化" && player.getTemporaryBuff().duration > 0) {
                std::cout << "(生效中: 剩余" << player.getTemporaryBuff().duration << "回合)";
            }
            else {
                std::cout << " (可用)";
            }

            std::cout << " - 消耗: " << skill->getCost() << " MP" << std::endl;
            index++;
        }

        // 获取玩家选择
        std::cout << "\n请选择行动 (0-" << skills.size() << "): ";
        std::cin >> choice;

        if (choice == 0) {
            // 普通攻击
            applyPlayerAttack();
            validChoice = true;
        }
        else if (choice >= 1 && choice <= skills.size()) {
            int skillIndex = choice - 1;

            // 检查技能是否可用
            if (!skills[skillIndex]->isReady()) {
                std::cout << "技能 " << skills[skillIndex]->getName() << " 还在冷却中!" << std::endl;
                std::cout << "请重新选择。" << std::endl;
            }
            else if (player.getMagicPowerCur() < skills[skillIndex]->getCost()) {
                std::cout << "魔力值不足，无法使用 " << skills[skillIndex]->getName() << "!" << std::endl;
                std::cout << "请重新选择。" << std::endl;
            }
            else if (skills[skillIndex]->getName() == "力量强化" && player.getTemporaryBuff().duration > 0) {
                std::cout << "技能 " << skills[skillIndex]->getName() << " 仍在生效中！" << std::endl;
                std::cout << "请重新选择。" << std::endl;
            }
            else {
                // 使用技能
                if (skills[skillIndex]->use(player, monster)) {
                    std::cout << "技能释放成功!" << std::endl;
                    validChoice = true;
                }
                else {
                    std::cout << "技能释放失败!" << std::endl;
                    std::cout << "请重新选择。" << std::endl;
                }
            }
        }
        else {
            std::cout << "无效的选择，请重新输入!" << std::endl;
        }
    }
}

void Battle::monsterTurn() {
    std::cout << "\n--- " << monster.getName() << " 的回合 ---" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 短暂暂停

    applyMonsterAttack();
}

bool Battle::isBattleOver() const {
    return player.getHealthCur() <= 0 || monster.getHealthCur() <= 0;
}

void Battle::applyPlayerAttack() {
    int playerAttack = player.getAttack() + player.getWeapon().getAttack() + player.getTemporaryBuff().attack_bonus;
    int damage = std::max(1, playerAttack); // 至少造成1点伤害

    std::cout << player.getName() << " 对 " << monster.getName() << " 造成了 " << damage << " 点伤害!" << std::endl;
    monster.setHealthCur(std::max(0, monster.getHealthCur() - damage));
}

void Battle::applyMonsterAttack() {
    int monsterAttack = monster.getAttack();
    int playerDefense = player.getDefense() + player.getArmor().getDefense() + player.getTemporaryBuff().defense_bonus;
    int damage = std::max(1, monsterAttack - playerDefense); // 至少造成1点伤害

    std::cout << monster.getName() << " 对 " << player.getName() << " 造成了 " << damage << " 点伤害!" << std::endl;
    player.setHealthCur(std::max(0, player.getHealthCur() - damage));
}