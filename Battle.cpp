#include "Battle.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Battle::Battle(Player& player, Monster& monster)
    : player(player), monster(monster), battleEnded(false) {
    srand(time(0)); // 初始化随机数种子
}

void Battle::start() {
    cout << "战斗开始！" << endl;
    cout << "玩家 " << player.getName() << " vs " << monster.getName() << endl;

    while (!battleEnded) {
        playerTurn();
        if (checkBattleEnd()) break;

        monsterTurn();
        checkBattleEnd();
    }
}

void Battle::playerTurn() {
    cout << "\n--- 玩家回合 ---" << endl;

    // 尝试使用技能
    Skill& skill = player.getSkill();
    if (skill.isReady() && player.getMagicPowerCur() >= skill.getCost()) {
        cout << "玩家使用技能: " << skill.getName() << endl;
        skill.use(player);
    }
    else {
        cout << "玩家未使用技能" << endl;
    }

    // 普通攻击
    int playerAttack = player.getAttack() + player.getEquipment().attack;
    int damage = playerAttack; // 怪物没有防御力
    monster.setHealthCur(monster.getHealthCur() - damage);

    cout << "玩家对怪物造成 " << damage << " 点伤害" << endl;
    cout << "怪物剩余生命值: " << monster.getHealthCur() << endl;
}

void Battle::monsterTurn() {
    cout << "\n--- 怪物回合 ---" << endl;

    // 检查是否使用特殊能力
    if (monster.hasSpecialAbility()) {
        int randomNum = rand() % 100;
        if (monster.useSpecialAbility(randomNum)) {
            cout << "怪物使用了特殊能力!" << endl;
        }
    }

    // 普通攻击
    int monsterAttack = monster.getAttack();
    int playerDefense = player.getDefense() + player.getEquipment().defense;
    int damage = monsterAttack - playerDefense;
    damage = damage > 0 ? damage : 0; // 确保伤害不为负

    player.setHealthCur(player.getHealthCur() - damage);

    cout << "怪物对玩家造成 " << damage << " 点伤害" << endl;
    cout << "玩家剩余生命值: " << player.getHealthCur() << endl;
}

bool Battle::checkBattleEnd() {
    if (player.getHealthCur() <= 0) {
        cout << "\n玩家失败！" << endl;
        battleEnded = true;
        return true;
    }

    if (monster.getHealthCur() <= 0) {
        cout << "\n玩家胜利！" << endl;
        // 掉落奖励
        int moneyDropped = monster.dropMoney(rand() % 100);
        player.setMoney(player.getMoney() + moneyDropped);
        cout << "获得 " << moneyDropped << " 绿宝石" << endl;
        battleEnded = true;
        return true;
    }

    return false;
}