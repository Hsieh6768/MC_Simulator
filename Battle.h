#ifndef BATTLE_H
#define BATTLE_H

#include "Player.h"
#include "Monster.h"

class Battle {
public:
    Battle(Player& player, Monster& monster);
    void start(); // ��ʼս��

private:
    Player& player;
    Monster& monster;

    void playerTurn();  // ��һغ�
    void monsterTurn(); // ����غ�
    bool isBattleOver() const; // ���ս���Ƿ����
    void applyPlayerAttack(); // �����ͨ����
    void applyMonsterAttack(); // ������ͨ����
};

#endif