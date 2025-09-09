#include "Battle.h"
#include "Player.h"
#include "Monster.h"
#include <iostream>

Battle::Battle(Player* player, Monster* monster)
    : m_player(player), m_monster(monster), m_isOver(false), m_result(0) {
}

void Battle::start() {
    std::cout << "战斗开始！" << std::endl;

    while (!isOver()) {
        // 玩家回合
        playerTurn();
        if (isOver()) break;

        // 怪物回合
        monsterTurn();
    }

    // 输出战斗结果
    if (m_result == 1) {
        std::cout << "恭喜你获得了胜利！" << std::endl;
    }
    else if (m_result == 2) {
        std::cout << "你被怪物击败了..." << std::endl;
    }
}

bool Battle::isOver() const {
    return m_isOver;
}

int Battle::getResult() const {
    return m_result;
}

void Battle::playerTurn() {
    std::cout << "\n----- 玩家回合 -----" << std::endl;

    // 显示状态
    std::cout << "玩家: HP=" << m_player->getHealth()
        << ", MP=" << m_player->getMana() << std::endl;
    std::cout << "怪物: HP=" << m_monster->getHealth() << std::endl;

    // 检查技能释放
    bool usedSkill = false;
    if (m_player->getMana() > 0) {
        char choice;
        std::cout << "是否使用技能? (y/n): ";
        std::cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            // 这里假设Player类有一个useSkill方法
            m_player->useSkill();
            usedSkill = true;
            std::cout << "玩家使用了技能!" << std::endl;
        }
    }

    if (!usedSkill) {
        std::cout << "玩家选择直接攻击" << std::endl;
    }

    // 玩家攻击怪物
    int damage = calculateDamage(m_player->getAttack(), 0); // 怪物防御力假设为0
    m_monster->setHealth(m_monster->getHealth() - damage);
    std::cout << "玩家对怪物造成了 " << damage << " 点伤害!" << std::endl;

    // 检查怪物是否死亡
    if (m_monster->getHealth() <= 0) {
        m_monster->setHealth(0);
        m_isOver = true;
        m_result = 1; // 玩家胜利
        std::cout << "怪物被击败了!" << std::endl;
    }
}

void Battle::monsterTurn() {
    std::cout << "\n----- 怪物回合 -----" << std::endl;

    // 怪物攻击玩家
    int damage = calculateDamage(m_monster->getAttack(), m_player->getDefense());
    m_player->setHealth(m_player->getHealth() - damage);
    std::cout << "怪物对玩家造成了 " << damage << " 点伤害!" << std::endl;

    // 检查玩家是否死亡
    if (m_player->getHealth() <= 0) {
        m_player->setHealth(0);
        m_isOver = true;
        m_result = 2; // 怪物胜利
        std::cout << "玩家被击败了!" << std::endl;
    }
}

int Battle::calculateDamage(int attack, int defense) const {
    int damage = attack - defense;
    return damage > 0 ? damage : 1; // 确保至少造成1点伤害
}