#ifndef BATTLE_H
#define BATTLE_H

#include "Player.h"
#include "Monster.h"

class Battle {
public:
    Battle(Player& player, Monster& monster);
    void start(); // 开始战斗

private:
    Player& player;
    Monster& monster;

    void playerTurn();  // 玩家回合
    void monsterTurn(); // 怪物回合
    bool isBattleOver() const; // 检查战斗是否结束
    void applyPlayerAttack(); // 玩家普通攻击
    void applyMonsterAttack(); // 怪物普通攻击
};

#endif