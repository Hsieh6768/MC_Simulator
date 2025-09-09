#include "Battle.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Battle::Battle(Player& player, Monster& monster)
    : player(player), monster(monster), battleEnded(false) {
    srand(time(0)); // ��ʼ�����������
}

void Battle::start() {
    cout << "ս����ʼ��" << endl;
    cout << "��� " << player.getName() << " vs " << monster.getName() << endl;

    while (!battleEnded) {
        playerTurn();
        if (checkBattleEnd()) break;

        monsterTurn();
        checkBattleEnd();
    }
}

void Battle::playerTurn() {
    cout << "\n--- ��һغ� ---" << endl;

    // ����ʹ�ü���
    Skill& skill = player.getSkill();
    if (skill.isReady() && player.getMagicPowerCur() >= skill.getCost()) {
        cout << "���ʹ�ü���: " << skill.getName() << endl;
        skill.use(player);
    }
    else {
        cout << "���δʹ�ü���" << endl;
    }

    // ��ͨ����
    int playerAttack = player.getAttack() + player.getEquipment().attack;
    int damage = playerAttack; // ����û�з�����
    monster.setHealthCur(monster.getHealthCur() - damage);

    cout << "��ҶԹ������ " << damage << " ���˺�" << endl;
    cout << "����ʣ������ֵ: " << monster.getHealthCur() << endl;
}

void Battle::monsterTurn() {
    cout << "\n--- ����غ� ---" << endl;

    // ����Ƿ�ʹ����������
    if (monster.hasSpecialAbility()) {
        int randomNum = rand() % 100;
        if (monster.useSpecialAbility(randomNum)) {
            cout << "����ʹ������������!" << endl;
        }
    }

    // ��ͨ����
    int monsterAttack = monster.getAttack();
    int playerDefense = player.getDefense() + player.getEquipment().defense;
    int damage = monsterAttack - playerDefense;
    damage = damage > 0 ? damage : 0; // ȷ���˺���Ϊ��

    player.setHealthCur(player.getHealthCur() - damage);

    cout << "����������� " << damage << " ���˺�" << endl;
    cout << "���ʣ������ֵ: " << player.getHealthCur() << endl;
}

bool Battle::checkBattleEnd() {
    if (player.getHealthCur() <= 0) {
        cout << "\n���ʧ�ܣ�" << endl;
        battleEnded = true;
        return true;
    }

    if (monster.getHealthCur() <= 0) {
        cout << "\n���ʤ����" << endl;
        // ���佱��
        int moneyDropped = monster.dropMoney(rand() % 100);
        player.setMoney(player.getMoney() + moneyDropped);
        cout << "��� " << moneyDropped << " �̱�ʯ" << endl;
        battleEnded = true;
        return true;
    }

    return false;
}