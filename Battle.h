#pragma once
#ifndef __BATTLE_H__
#define __BATTLE_H__
#include "Monster.h"
#include "Player.h"
class Battle {
public:
	void beginBattle();//开始战斗
	bool showResult();//战斗结果，成功获得战利品，失败回到村庄
private:
	int backupPlayerLife;//战斗前生命，在死亡的时候恢复
	int backupPlayerEnergy;//战斗前法力值，在死亡的时候恢复
	int judegeEnd();//1 玩家赢  -1 怪物赢  0 继续战斗

};
#endif 