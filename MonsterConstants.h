#ifndef MONSTER_CONSTANTS_H
#define MONSTER_CONSTANTS_H

// ��������̱�ʯ�Ļ���ֵ�ͷ�Χ
namespace DropConstants {
    // ��ʬ Zombie
    const int ZOMBIE_BASE_DROP = 1;
    const int ZOMBIE_DROP_RANGE = 4;  // ���䷶Χ: 1-4

    // ���� Piglin
    const int PIGLIN_BASE_DROP = 3;
    const int PIGLIN_DROP_RANGE = 5;  // ���䷶Χ: 3-7

    // ֩�� Spider
    const int SPIDER_BASE_DROP = 2;
    const int SPIDER_DROP_RANGE = 5;  // ���䷶Χ: 2-6

    // �������� Wither Skeleton
    const int WITHER_SKELETON_BASE_DROP = 8;
    const int WITHER_SKELETON_DROP_RANGE = 8;  // ���䷶Χ: 8-15

    // �ս�ʹ�� Enderman
    const int ENDERMAN_BASE_DROP = 10;
    const int ENDERMAN_DROP_RANGE = 11;  // ���䷶Χ: 10-20

    // ����ʹ�� Blaze
    const int BLAZE_BASE_DROP = 15;
    const int BLAZE_DROP_RANGE = 16;  // ���䷶Χ: 15-30

    // �ս��� Ender Dragon
    const int ENDER_DRAGON_BASE_DROP = 100;
    const int ENDER_DRAGON_DROP_RANGE = 101;  // ���䷶Χ: 100-200
}

// ���ڼ�������Ƿ񴥷����������ĳ���N���������N����������Ϊ1ʱ����
namespace SpecialAbilityConstants {
    // �������� Wither Skeleton
    const int WITHER_SKELETON_N = 3;

    // �ս�ʹ�� Enderman
    const int ENDERMAN_N = 3;

    // ����ʹ�� Blaze
    const int BLAZE_N = 4;

    // �ս��� Ender Dragon
    const int ENDER_DRAGON_N = 6;
}

#endif
