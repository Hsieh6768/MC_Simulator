#ifndef BATTLE_H
#define BATTLE_H

#include "Player.h"
#include "Monster.h"

class Battle {
private:
    Player& player;
    Monster& monster;
    bool battleEnded;

    void playerTurn();
    void monsterTurn();
    bool checkBattleEnd();

public:
    Battle(Player& player, Monster& monster);
    void start();
};

#endif