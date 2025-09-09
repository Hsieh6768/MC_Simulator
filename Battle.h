#ifndef BATTLE_H
#define BATTLE_H

// 前向声明，避免循环包含
class Player;
class Monster;

class Battle {
public:
    // 构造函数，传入玩家和怪物指针
    Battle(Player* player, Monster* monster);

    // 开始战斗
    void start();

    // 判断战斗是否结束
    bool isOver() const;

    // 获取战斗结果
    int getResult() const; // 0:未结束, 1:玩家胜利, 2:怪物胜利

private:
    Player* m_player;    // 玩家指针
    Monster* m_monster;  // 怪物指针
    bool m_isOver;       // 战斗是否结束
    int m_result;        // 战斗结果

    // 玩家回合
    void playerTurn();

    // 怪物回合
    void monsterTurn();

    // 计算伤害
    int calculateDamage(int attack, int defense) const;
};

#endif