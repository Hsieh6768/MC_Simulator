#ifndef MONSTER_CONSTANTS_H
#define MONSTER_CONSTANTS_H

// 怪物掉落绿宝石的基础值和范围
namespace DropConstants {
    // 僵尸 Zombie
    const int ZOMBIE_BASE_DROP = 1;
    const int ZOMBIE_DROP_RANGE = 4;  // 掉落范围: 1-4

    // 猪灵 Piglin
    const int PIGLIN_BASE_DROP = 3;
    const int PIGLIN_DROP_RANGE = 5;  // 掉落范围: 3-7

    // 蜘蛛 Spider
    const int SPIDER_BASE_DROP = 2;
    const int SPIDER_DROP_RANGE = 5;  // 掉落范围: 2-6

    // 凋零骷髅 Wither Skeleton
    const int WITHER_SKELETON_BASE_DROP = 8;
    const int WITHER_SKELETON_DROP_RANGE = 8;  // 掉落范围: 8-15

    // 终界使者 Enderman
    const int ENDERMAN_BASE_DROP = 10;
    const int ENDERMAN_DROP_RANGE = 11;  // 掉落范围: 10-20

    // 烈焰使者 Blaze
    const int BLAZE_BASE_DROP = 15;
    const int BLAZE_DROP_RANGE = 16;  // 掉落范围: 15-30

    // 终界龙 Ender Dragon
    const int ENDER_DRAGON_BASE_DROP = 100;
    const int ENDER_DRAGON_DROP_RANGE = 101;  // 掉落范围: 100-200
}

// 用于计算怪物是否触发特殊能力的除数N，随机数对N求余且余数为1时触发
namespace SpecialAbilityConstants {
    // 凋零骷髅 Wither Skeleton
    const int WITHER_SKELETON_N = 3;

    // 终界使者 Enderman
    const int ENDERMAN_N = 3;

    // 烈焰使者 Blaze
    const int BLAZE_N = 4;

    // 终界龙 Ender Dragon
    const int ENDER_DRAGON_N = 6;
}

#endif
