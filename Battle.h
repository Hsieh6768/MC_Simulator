#ifndef BATTLE_H
#define BATTLE_H

// ǰ������������ѭ������
class Player;
class Monster;

class Battle {
public:
    // ���캯����������Һ͹���ָ��
    Battle(Player* player, Monster* monster);

    // ��ʼս��
    void start();

    // �ж�ս���Ƿ����
    bool isOver() const;

    // ��ȡս�����
    int getResult() const; // 0:δ����, 1:���ʤ��, 2:����ʤ��

private:
    Player* m_player;    // ���ָ��
    Monster* m_monster;  // ����ָ��
    bool m_isOver;       // ս���Ƿ����
    int m_result;        // ս�����

    // ��һغ�
    void playerTurn();

    // ����غ�
    void monsterTurn();

    // �����˺�
    int calculateDamage(int attack, int defense) const;
};

#endif