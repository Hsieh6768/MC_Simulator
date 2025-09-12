#include "Battle.h"
#include "Skill.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <Windows.h>

using namespace std;

Battle::Battle(Player& player, Monster& monster)
    : player(player), monster(monster), round(0), monsterBuff{ 0, 0 }, monsterDodged(false) {
}

void Battle::start() {
    system("cls");
    cout << "战斗开始! " << player.getName() << " vs " << monster.getName() << endl;
    Sleep(1200);

    while (!isBattleOver()) {
        round++;

        // 玩家回合
        playerTurn();
        if (isBattleOver()) 
            break;

        // 更新怪物增益状态
        if (monsterBuff.duration > 0) {
            monsterBuff.duration--;
            if (monsterBuff.duration == 0) {
                monsterBuff.attack_bonus = 0;
            }
        }
        monsterDodged = false; // 重置闪避状态

        // 怪物回合
        monsterTurn();
    }
}

void Battle::playerTurn() {
    // 回合开始处理
    player.updateBuffs();
    vector<unique_ptr<Skill>>& skills = player.getSkill();
    for (auto& skill : skills) {
        skill->reduceCooldown();
    }

    system("cls");
    cout << "--- " << player.getName() << " 的回合 ---" << endl;
    player.showInfo();
    cout << monster.getName() << " 生命值: " << monster.getHealthCur() << "/" << monster.getHealthMax() << endl;

    int choice;
    bool validChoice = false;

    while (!validChoice) {
        // 显示所有技能及其状态
        cout << "\n行动列表:" << endl;

        cout << "\n0. 普通攻击" << endl;
        int index = 0;
        for (auto& skill : skills) {
            cout << index + 1 << ". " << skill->getName();

            if (!skill->isReady()) {
                cout << " (冷却中: " << skill->getCurrentCooldown() << "回合)";
            }
            else if (player.getMagicPowerCur() < skill->getCost()) {
                cout << " (魔法不足)";
            }
            else if (skill->getName() == "力量强化" && player.getTemporaryBuff().duration > 0) {
                cout << "(生效中: 剩余" << player.getTemporaryBuff().duration << "回合)";
            }
            else {
                cout << " (可用)";
            }

            cout << " - 消耗: " << skill->getCost() << " MP" << endl;
            index++;
        }

        // 获取玩家选择
        cout << "\n请选择行动 (0-" << skills.size() << "): ";
        cin >> choice;

        if (choice == 0) {
            // 普通攻击
            cout << "玩家 " << player.getName() << " 使用了普通攻击" << endl;
            applyPlayerAttack();
            Sleep(1200);
            validChoice = true;
        }
        else if (choice >= 1 && choice <= skills.size()) {
            int skillIndex = choice - 1;

            // 检查技能是否可用
            if (!skills[skillIndex]->isReady()) {
                system("cls");
                cout << "技能 " << skills[skillIndex]->getName() << " 还在冷却中!" << endl;
                cout << "请重新选择。" << endl;
                Sleep(1200);
            }
            else if (player.getMagicPowerCur() < skills[skillIndex]->getCost()) {
                system("cls");
                cout << "魔力值不足，无法使用 " << skills[skillIndex]->getName() << "!" << endl;
                cout << "请重新选择。" << endl;
                Sleep(1200);
            }
            else if (skills[skillIndex]->getName() == "力量强化" && player.getTemporaryBuff().duration > 0) {
                system("cls");
                cout << "技能 " << skills[skillIndex]->getName() << " 仍在生效中！" << endl;
                cout << "请重新选择。" << endl;
                Sleep(1200);
            }
            else {
                // 使用技能
                if (skills[skillIndex]->use(player, monster)) {
                    system("cls");
                    cout << "技能释放成功!" << endl;
                    Sleep(1200);
                    validChoice = true;
                }
                else {
                    system("cls");
                    cout << "技能释放失败!" << endl;
                    cout << "请重新选择。" << endl;
                    Sleep(1200);
                }
            }
        }
        else {
            system("cls");
            cout << "无效的选择，请重新输入!" << endl;
            Sleep(1200);
        }
    }

    // 每三回合回复一点魔力值
    if (round % 3 == 0) {
        player.setMagicPowerCur(max(player.getMagicPowerCur() + 1, player.getMagicPowerMax()));
    }
}

void Battle::monsterTurn() {
    system("cls");
    cout << "--- " << monster.getName() << " 的回合 ---" << endl;
    Sleep(1200);

    if (monster.useSpecialAbility(rand())) {
        string abilityName = monster.getAbility(0); // 获取第一个特殊能力名称

        // 根据怪物类型和能力名称处理特殊效果
        if (monster.getName() == "凋零骷髅" && abilityName == "凋零诅咒") {
            cout << "怪物 " << monster.getName() << " 使用了 " << abilityName << endl;
            monsterBuff.attack_bonus += 1;
            monsterBuff.duration = 3;
            cout << monster.getName() << " 使你每回合额外受到 1 点凋零伤害，持续 3 回合" << endl;
            applyMonsterAttack();
        }
        else if (monster.getName() == "终界使者" && abilityName == "瞬间移动") {
            cout << "怪物 " << monster.getName() << " 使用了 " << abilityName << endl;
            monsterDodged = true;
            cout << monster.getName() << " 闪避了下一次攻击" << endl;
        }
        else if (monster.getName() == "烈焰使者" && abilityName == "火球攻击") {
            cout << "怪物 " << monster.getName() << " 使用了 " << abilityName << endl;
            monsterBuff.attack_bonus += 4;
            monsterBuff.duration = 1;
            cout << monster.getName() << " 本回合攻击力提升 4 点" << endl;
            applyMonsterAttack();
        }
        else if (monster.getName() == "终界龙") {
            // 终界龙随机选择一个特殊能力，
            int abilityIndex = rand() % 2;
            abilityName = monster.getAbility(abilityIndex);
            cout << "怪物 " << monster.getName() << " 使用了 " << abilityName << endl;

            if (abilityName == "冲撞攻击") {
                int damage = 18;
                player.setHealthCur(max(0, player.getHealthCur() - damage));
                cout << monster.getName() << " 冲撞攻击造成 " << damage << " 点伤害!" << endl;
            }
            else if (abilityName == "龙息腐蚀") {
                monsterBuff.attack_bonus += 3;
                monsterBuff.duration = 3;
                cout << monster.getName() << " 使你每回合受到 3 点腐蚀伤害，持续 3 回合" << endl;
            }
        }
        else {
            cout << "怪物 " << monster.getName() << " 使用了 " << abilityName << endl;
        }
        Sleep(1200);
    }
    else {
        cout << "怪物 " << monster.getName() << " 使用了普通攻击" << endl;
        applyMonsterAttack();
        Sleep(1200);
    }
}

bool Battle::isBattleOver() const {
    return player.getHealthCur() <= 0 || monster.getHealthCur() <= 0;
}

void Battle::applyPlayerAttack() {
    // 检查怪物是否闪避
    if (monsterDodged) {
        cout << monster.getName() << " 闪避了攻击！" << endl;
        return;
    }

    int playerAttack = player.getAttack() + player.getWeapon().getAttack() + player.getTemporaryBuff().attack_bonus;
    int damage = max(1, playerAttack); // 至少造成1点伤害

    cout << player.getName() << " 对 " << monster.getName() << " 造成了 " << damage << " 点伤害!" << endl;
    monster.setHealthCur(max(0, monster.getHealthCur() - damage));
}

void Battle::applyMonsterAttack() {
    int monsterAttack = monster.getAttack() + monsterBuff.attack_bonus;
    int playerDefense = player.getDefense() + player.getArmor().getDefense() + player.getTemporaryBuff().defense_bonus;
    int damage = max(1, monsterAttack - playerDefense); // 至少造成1点伤害

    cout << monster.getName() << " 对 " << player.getName() << " 造成了 " << damage << " 点伤害!" << endl;
    player.setHealthCur(max(0, player.getHealthCur() - damage));
}