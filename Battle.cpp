#include "Battle.h"
#include "Skill.h"
#include "CommandInput.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <Windows.h>

using namespace std;

Battle::Battle(Player& player, Monster& monster, int round)
    : player(player), monster(monster), round(round) {
}

void Battle::start() {
    system("cls");
    cout << "战斗开始!\n";
    ColorManager::COLOR_PRINT(player.getName(), YELLOW);
    cout << " vs ";
    ColorManager::COLOR_PRINT(monster.getName(), RED);
    cout << endl;
    Sleep(1200);

    while (!isBattleOver()) {
        round++;

        // 玩家回合
        playerTurn();
        if (isBattleOver()) 
            break;

        // 怪物回合
        monsterTurn();
    }
}

void Battle::playerTurn() {
    // 回合开始处理
    player.updatePlayerBuffs();
    vector<unique_ptr<Skill>>& skills = player.getSkill();
    for (auto& skill : skills) {
        skill->reduceCooldown();
    }

    int choice = 0;
    bool validChoice = false;

    while (!validChoice) {
        system("cls");
        ColorManager::COLOR_PRINT("回合 ", YELLOW);
        cout << round << endl;
        ColorManager::COLOR_PRINT("\n--- ", YELLOW);
        ColorManager::COLOR_PRINT(player.getName(), YELLOW);
        ColorManager::COLOR_PRINT(" 的回合 ---\n", YELLOW);
        player.showInfo();
        cout << endl;
        ColorManager::COLOR_PRINT(monster.getName(), RED);
        cout << " 生命值: " << monster.getHealthCur() << "/" << monster.getHealthMax() << endl;

        // 显示所有技能及其状态
        cout << "\n行动列表:" << endl;

        cout << "\n0. 普通攻击" << endl;
        int index = 0;
        for (auto& skill : skills) {
            cout << index + 1 << ". ";
            ColorManager::COLOR_PRINT(skill->getName(), BLUE);

            if (!skill->isReady()) {
                cout << " (冷却中: " << skill->getCurrentCooldown() << "回合)";
            }
            else if (player.getMagicPowerCur() < skill->getCost()) {
                cout << " (魔法不足)";
            }
            else if (skill->getName() == "力量强化" && player.getPlayerBuff().duration > 0) {
                cout << "(生效中: 剩余" << player.getPlayerBuff().duration << "回合)";
            }
            else {
                cout << " (可用)";
            }

            cout << " - 消耗: " << skill->getCost() << " MP" << endl;
            index++;
        }

        // 获取玩家选择
        cout << "\n请选择行动 (0-" << skills.size() << "): ";

        string input;
        cin >> input;
        choice = convertChineseCommand(input);

        if (choice == -1) {
            system("cls");
            cout << "无效的选择，请重新输入！" << endl;
            Sleep(1200);
            continue;
        }

        if (choice == 0) {
            // 普通攻击
            cout << "玩家 ";
            ColorManager::COLOR_PRINT(player.getName(), YELLOW);
            cout << " 使用了普通攻击" << endl;
            applyPlayerAttack();
            Sleep(1200);
            validChoice = true;
        }
        else if (choice >= 1 && choice <= skills.size()) {
            int skillIndex = choice - 1;

            // 检查技能是否可用
            if (!skills[skillIndex]->isReady()) {
                system("cls");
                cout << "技能 ";
                ColorManager::COLOR_PRINT(skills[skillIndex]->getName(), BLUE);
                cout << " 还在冷却中!" << endl;
                cout << "请重新选择。" << endl;
                Sleep(1200);
            }
            else if (player.getMagicPowerCur() < skills[skillIndex]->getCost()) {
                system("cls");
                cout << "魔力值不足，无法使用 ";
                ColorManager::COLOR_PRINT(skills[skillIndex]->getName(), BLUE);
                cout << "!" << endl;
                cout << "请重新选择。" << endl;
                Sleep(1200);
            }
            else if (skills[skillIndex]->getName() == "力量强化" && player.getPlayerBuff().duration > 0) {
                system("cls");
                cout << "技能 ";
                ColorManager::COLOR_PRINT(skills[skillIndex]->getName(), BLUE);
                cout << " 仍在生效中！" << endl;
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

    // 每两回合回复一点生命值
    if (round % 2 == 0) {
        player.setHealthCur(min(player.getHealthCur() + 1, player.getHealthMax()));
    }
    // 每三回合回复一点魔力值
    if (round % 3 == 0) {
        player.setMagicPowerCur(min(player.getMagicPowerCur() + 1, player.getMagicPowerMax()));
    }
}

void Battle::monsterTurn() {
    monster.updateMonsterBuffs();

    system("cls");
    ColorManager::COLOR_PRINT("--- ", RED);
    ColorManager::COLOR_PRINT(monster.getName(), RED);
    ColorManager::COLOR_PRINT(" 的回合 ---\n", RED);
    Sleep(1200);

    if (monster.useSpecialAbility(rand())) {
        string abilityName = monster.getAbility(0); // 获取第一个特殊能力名称

        // 根据怪物类型和能力名称处理特殊效果
        if (monster.getName() == "凋零骷髅" && abilityName == "凋零诅咒" && !monster.getMonsterBuff().activated) {
            cout << "怪物 ";
            ColorManager::COLOR_PRINT(monster.getName(), RED);
            cout << " 使用了 " << abilityName << endl;

            monster.setMonsterBuff({ 1, 3, true, false });

            ColorManager::COLOR_PRINT(monster.getName(), RED);
            cout << " 使你每回合额外受到 1 点凋零伤害，持续 3 回合" << endl;
            applyMonsterAttack();
        }
        else if (monster.getName() == "终界使者" && abilityName == "瞬间移动") {
            cout << "怪物 ";
            ColorManager::COLOR_PRINT(monster.getName(), RED);
            cout << " 使用了 " << abilityName << endl;

            monster.setMonsterBuff({ 
                monster.getMonsterBuff().attack_bonus, 
                monster.getMonsterBuff().duration, 
                monster.getMonsterBuff().activated, 
                true 
                });

            ColorManager::COLOR_PRINT(monster.getName(), RED);
            cout << " 闪避了下一次攻击" << endl;
            applyMonsterAttack();
        }
        else if (monster.getName() == "烈焰使者" && abilityName == "火球攻击") {
            cout << "怪物 ";
            ColorManager::COLOR_PRINT(monster.getName(), RED);
            cout << " 使用了 " << abilityName << endl;

            monster.setMonsterBuff({ 4, 1, true, false });

            ColorManager::COLOR_PRINT(monster.getName(), RED);
            cout << " 本回合攻击力提升 4 点" << endl;
            applyMonsterAttack();
        }
        else if (monster.getName() == "终界龙") {
            // 终界龙随机选择一个特殊能力，
            int abilityIndex = rand() % 2;
            abilityName = monster.getAbility(abilityIndex);

            cout << "怪物 ";
            ColorManager::COLOR_PRINT(monster.getName(), RED);
            cout << " 使用了 " << abilityName << endl;

            if (abilityName == "冲撞攻击") {
                // 不使用 MonsterBuff 方法以避免与 "龙息腐蚀" 技能发生冲突
                int monsterAttack = 18 + monster.getMonsterBuff().attack_bonus;
                int playerDefense = player.getDefense() + player.getArmor().getDefense() + player.getPlayerBuff().defense_bonus;
                int damage = monsterAttack - playerDefense;
                player.setHealthCur(max(0, player.getHealthCur() - damage));

                ColorManager::COLOR_PRINT(monster.getName(), RED);
                cout << " 冲撞攻击造成 " << damage << " 点伤害!" << endl;
            }
            else if (abilityName == "龙息腐蚀" && !monster.getMonsterBuff().activated) {
                monster.setMonsterBuff({ 2, 3, true, false });

                ColorManager::COLOR_PRINT(monster.getName(), RED);
                cout << " 使 ";
                ColorManager::COLOR_PRINT(player.getName(), YELLOW);
                cout << " 每回合受到 2 点腐蚀伤害，持续 3 回合" << endl;
            }
        }
        else {
            cout << "怪物 " << monster.getName() << " 使用了 " << abilityName << endl;
        }
    }
    else {
        cout << "怪物 ";
        ColorManager::COLOR_PRINT(monster.getName(), RED);
        cout << " 使用了普通攻击" << endl;
        applyMonsterAttack();
    }
    Sleep(1200);
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    cout << "\n按回车键继续...";
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
}

bool Battle::isBattleOver() const {
    return player.getHealthCur() <= 0 || monster.getHealthCur() <= 0;
}

void Battle::applyPlayerAttack() {
    // 检查怪物是否闪避
    if (monster.getMonsterBuff().dodged) {
        ColorManager::COLOR_PRINT(monster.getName(), RED);
        cout << " 闪避了攻击！" << endl;
        return;
    }

    int playerAttack = player.getAttack() + player.getWeapon().getAttack() + player.getPlayerBuff().attack_bonus;
    int damage = max(1, playerAttack);  // 至少造成1点伤害

    ColorManager::COLOR_PRINT(player.getName(), YELLOW);
    cout << " 对 ";
    ColorManager::COLOR_PRINT(monster.getName(), RED);
    cout << " 造成了 " << damage << " 点伤害!" << endl;
    monster.setHealthCur(max(0, monster.getHealthCur() - damage));
}

void Battle::applyMonsterAttack() {
    int monsterAttack = monster.getAttack() + monster.getMonsterBuff().attack_bonus;
    int playerDefense = player.getDefense() + player.getArmor().getDefense() + player.getPlayerBuff().defense_bonus;
    int damage = max(1, monsterAttack - playerDefense);  // 至少造成1点伤害

    ColorManager::COLOR_PRINT(monster.getName(), RED);
    cout << " 对 ";
    ColorManager::COLOR_PRINT(player.getName(), YELLOW);
    cout << " 造成了 " << damage << " 点伤害!" << endl;
    player.setHealthCur(max(0, player.getHealthCur() - damage));
}