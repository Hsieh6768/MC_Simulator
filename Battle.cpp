#include "Battle.h"
#include <iostream>
#include <thread>
#include <chrono>

Battle::Battle(Player& player, Monster& monster)
    : player(player), monster(monster) {
}

void Battle::start() {
    std::cout << "ս����ʼ! " << player.getName() << " vs " << monster.getName() << std::endl;

    while (!isBattleOver()) {
        // ��һغ�
        playerTurn();
        if (isBattleOver()) break;

        // ����غ�
        monsterTurn();
    }

    // ս�����
    if (player.getHealthCur() <= 0) {
        std::cout << player.getName() << " ��������!" << std::endl;
    }
    else {
        std::cout << monster.getName() << " ��������!" << std::endl;
        // ��һ�ý���
        int moneyEarned = monster.dropMoney(rand() % 100); // ��������̱�ʯ
        player.setMoney(player.getMoney() + moneyEarned);
        std::cout << player.getName() << " ����� " << moneyEarned << " �̱�ʯ!" << std::endl;
    }
}

void Battle::playerTurn() {
    std::cout << "\n--- " << player.getName() << "�Ļغ� ---" << std::endl;
    player.showInfo();
    std::cout << monster.getName() << " ����ֵ: " << monster.getHealthCur() << "/" << monster.getHealthMax() << std::endl;

    // ����Ƿ�����ͷż���
    Skill playerSkill = player.getSkill();
    if (playerSkill.isReady() && player.getMagicPowerCur() >= playerSkill.getCost()) {
        std::cout << "�Ƿ�ʹ�ü��� " << playerSkill.getName() << "? (y/n): ";
        char choice;
        std::cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            if (playerSkill.use(player)) {
                std::cout << "�����ͷųɹ�!" << std::endl;
            }
            else {
                std::cout << "�����ͷ�ʧ��!" << std::endl;
            }
        }
    }

    // ��ͨ����
    applyPlayerAttack();

    // ���ټ�����ȴ
    playerSkill.reduceCooldown();
}

void Battle::monsterTurn() {
    std::cout << "\n--- " << monster.getName() << "�Ļغ� ---" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // ������ͣ

    applyMonsterAttack();
}

bool Battle::isBattleOver() const {
    return player.getHealthCur() <= 0 || monster.getHealthCur() <= 0;
}

void Battle::applyPlayerAttack() {
    int playerAttack = player.getAttack() + player.getEquipment().attack;
    int damage = std::max(1, playerAttack); // �������1���˺�

    std::cout << player.getName() << " �� " << monster.getName() << " ����� " << damage << " ���˺�!" << std::endl;
    monster.setHealthCur(monster.getHealthCur() - damage);
}

void Battle::applyMonsterAttack() {
    int monsterAttack = monster.getAttack();
    int playerDefense = player.getDefense() + player.getEquipment().defense;
    int damage = std::max(1, monsterAttack - playerDefense); // �������1���˺�

    std::cout << monster.getName() << " �� " << player.getName() << " ����� " << damage << " ���˺�!" << std::endl;
    player.setHealthCur(player.getHealthCur() - damage);
}