#pragma once
#ifndef __BATTLE_H__
#define __BATTLE_H__
#include "Monster.h"
#include "Player.h"
class Battle {
public:
	void beginBattle();//��ʼս��
	bool showResult();//ս��������ɹ����ս��Ʒ��ʧ�ܻص���ׯ
private:
	int backupPlayerLife;//ս��ǰ��������������ʱ��ָ�
	int backupPlayerEnergy;//ս��ǰ����ֵ����������ʱ��ָ�
	int judegeEnd();//1 ���Ӯ  -1 ����Ӯ  0 ����ս��

};
#endif 