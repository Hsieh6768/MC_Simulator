#pragma once
#ifndef EQUIPMENT_H
#define EQUIPMENT_H

// ǰ������Player��
class Player;

class Equipment {
private:
    int ATK; // װ���ṩ�Ĺ������ӳ�
    int DEF; // װ���ṩ�ķ������ӳ�

public:
    // ���캯��
    Equipment(int atk = 0, int def = 0);

    // ��ȡ����װ�������ҹ�����
    int getPlayerATK(const Player& player) const;

    // ��ȡ����װ�������ҷ�����
    int getPlayerDEF(const Player& player) const;

    // ����װ������
    void setATK(int atk);
    void setDEF(int def);

    // ��ȡװ������
    int getATK() const;
    int getDEF() const;
};

#endif // EQUIPMENT_H