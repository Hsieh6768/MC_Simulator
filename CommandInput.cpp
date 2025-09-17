#include "CommandInput.h"
#include <algorithm>
#include <cctype>

using namespace std;

// 定义变量和函数
map<string, int> chineseCommands = {
    {"新的游戏", 1},
    {"加载游戏", 2},
    {"退出", 3},
    {"移动", 1},
    {"战斗", 2},
    {"交易", 3},
    {"恢复", 4},
    {"查看面板", 5},
    {"查看地图", 6},
    {"保存游戏", 7},
    {"退出游戏", 8},
    {"退回游戏首页", 9},
    {"播放终末之诗", 10},
    {"打开宝藏", 11},
    {"武器", 1},
    {"护甲", 2},
    {"离开商店", 3},
    {"是", 1},
    {"否", 0},
    {"取消", 0},
    {"确认", 1},
    {"木剑", 1},
    {"铁剑", 2},
    {"钻石剑", 3},
    {"皮革甲", 1},
    {"铁甲", 2},
    {"钻石甲", 3},
    {"返回", 4},
    {"回到战斗前", 1},
    {"退回到游戏首页", 2},
    {"普通攻击", 0},
    {"火球术", 1},
    {"治疗术", 2},
    {"力量强化", 3}
};

int convertChineseCommand(const string& input) {
    string lowerInput = input;
    transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);

    for (const auto& pair : chineseCommands) {
        string lowerCommand = pair.first;
        transform(lowerCommand.begin(), lowerCommand.end(), lowerCommand.begin(), ::tolower);

        if (lowerInput.find(lowerCommand) != string::npos) {
            return pair.second;
        }
    }

    // 尝试将输入直接转换为数字
    try {
        return stoi(input);
    }
    catch (...) {
        return -1; // 无效输入
    }
}