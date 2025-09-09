#include "Battle.h"
#include "Player.h"
#include "Monster.h"
#include <iostream>

Battle::Battle(Player* player, Monster* monster)
    : m_player(player), m_monster(monster), m_isOver(false), m_result(0) {
}

void Battle::start() {
    std::cout << "ս����ʼ��" << std::endl;

    while (!isOver()) {
        // ��һغ�
        playerTurn();
        if (isOver()) break;

        // ����غ�
        monsterTurn();
    }

    // ���ս�����
    if (m_result == 1) {
        std::cout << "��ϲ������ʤ����" << std::endl;
    }
    else if (m_result == 2) {
        std::cout << "�㱻���������..." << std::endl;
    }
}

bool Battle::isOver() const {
    return m_isOver;
}

int Battle::getResult() const {
    return m_result;
}

void Battle::playerTurn() {
    std::cout << "\n----- ��һغ� -----" << std::endl;

    // ��ʾ״̬
    std::cout << "���: HP=" << m_player->getHealth()
        << ", MP=" << m_player->getMana() << std::endl;
    std::cout << "����: HP=" << m_monster->getHealth() << std::endl;

    // ��鼼���ͷ�
    bool usedSkill = false;
    if (m_player->getMana() > 0) {
        char choice;
        std::cout << "�Ƿ�ʹ�ü���? (y/n): ";
        std::cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            // �������Player����һ��useSkill����
            m_player->useSkill();
            usedSkill = true;
            std::cout << "���ʹ���˼���!" << std::endl;
        }
    }

    if (!usedSkill) {
        std::cout << "���ѡ��ֱ�ӹ���" << std::endl;
    }

    // ��ҹ�������
    int damage = calculateDamage(m_player->getAttack(), 0); // �������������Ϊ0
    m_monster->setHealth(m_monster->getHealth() - damage);
    std::cout << "��ҶԹ�������� " << damage << " ���˺�!" << std::endl;

    // �������Ƿ�����
    if (m_monster->getHealth() <= 0) {
        m_monster->setHealth(0);
        m_isOver = true;
        m_result = 1; // ���ʤ��
        std::cout << "���ﱻ������!" << std::endl;
    }
}

void Battle::monsterTurn() {
    std::cout << "\n----- ����غ� -----" << std::endl;

    // ���﹥�����
    int damage = calculateDamage(m_monster->getAttack(), m_player->getDefense());
    m_player->setHealth(m_player->getHealth() - damage);
    std::cout << "������������� " << damage << " ���˺�!" << std::endl;

    // �������Ƿ�����
    if (m_player->getHealth() <= 0) {
        m_player->setHealth(0);
        m_isOver = true;
        m_result = 2; // ����ʤ��
        std::cout << "��ұ�������!" << std::endl;
    }
}

int Battle::calculateDamage(int attack, int defense) const {
    int damage = attack - defense;
    return damage > 0 ? damage : 1; // ȷ���������1���˺�
}