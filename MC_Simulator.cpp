#include <iostream>
#include <windows.h>
#include "Command.h"
#include "Battle.h"
#include "Map.h"
#include "Player.h"
#include "Monster.h"

using namespace std;

void displayMainMenu() {
    system("cls");
    cout << "========================================" << endl;
    cout << "            MC Simulator" << endl;
    cout << "========================================" << endl;
    cout << "1. 开始新游戏" << endl;
    cout << "2. 加载游戏" << endl;
    cout << "3. 退出游戏" << endl;
    cout << "请选择: ";
}

void displayGameMenu() {
    system("cls");
    cout << "\n========================================" << endl;
    cout << "                游戏菜单" << endl;
    cout << "========================================" << endl;
    cout << "1. 移动" << endl;
    cout << "2. 战斗" << endl;
    cout << "3. 交易" << endl;
    cout << "4. 恢复" << endl;
    cout << "5. 查看面板" << endl;
    cout << "6. 查看地图" << endl;
    cout << "7. 保存游戏" << endl;
    cout << "8. 退出游戏" << endl;
    cout << "请选择: ";
}
int main() {
    while (true) {
        Player player;
        Map map;
        Command command(player, map);

        // 进入主页面
        bool in_game = false;
        while (!in_game) {
            displayMainMenu();
            int game_choice;
            cin >> game_choice;

            if (game_choice == 1) {
                command.newGame();
                in_game = true;
            }
            else if (game_choice == 2) {
                if (command.loadGame("Mc_Simulator.txt")) {
                    in_game = true;
                }
            }
            else if (game_choice == 3) {
                system("cls");
                cout << "感谢游玩！再见！" << endl;
                Sleep(1200);
                return 0;
            }
            else {
                system("cls");
                cout << "无效的选择，请重新输入！" << endl;
                Sleep(1200);
            }
        }

        // 游戏主循环
        bool game_running = true;
        while (game_running) {
            // 显示当前位置信息
            map.displayCurrentPosition();

            // 显示游戏菜单
            displayGameMenu();
            int operation_choice;
            cin >> operation_choice;

            switch (operation_choice) {
            case 1:
                system("cls");
                command.move();
                break;
            case 2:
                system("cls");
                command.battleSelection();
                break;
            case 3:
                system("cls");
                command.trade();
                break;
            case 4:
                system("cls");
                command.recover();
                break;
            case 5:
                system("cls");
                command.panel();
                break;
            case 6:
                system("cls");
                command.showMap();
                break;
            case 7:
                system("cls");
                command.saveGame("Mc_Simulator.txt");
                break;
            case 8:
                system("cls");
                command.exitGame();
                game_running = false;
                break;
            default:
                system("cls");
                cout << "无效的选择，请重新输入！" << endl;
                Sleep(1200);
            }

            // 检查玩家是否死亡
            if (player.getHealthCur() <= 0) {
                system("cls");
                cout << "\n========================================" << endl;
                cout << "            你已被击败！" << endl;
                cout << "========================================" << endl;
                cout << "1. 回到战斗前" << endl;
                cout << "2. 退出到主菜单" << endl;
                cout << "请选择: ";

                int death_choice;
                cin >> death_choice;

                if (death_choice == 1) {
                    if (command.loadGame("autosave.txt")) {
                        system("cls");
                        cout << "已加载，回到战斗前状态。" << endl;
                        Sleep(1200);
                    }
                    else {
                        system("cls");
                        cout << "加载失败！返回主页面。" << endl;
                        Sleep(1200);
                        game_running = false;  // 跳出游戏循环，回到主页面
                    }
                }
                else {
                    game_running = false;  // 跳出游戏循环，回到主页面
                }
            }
        }
        system("cls");
        cout << "返回主页面..." << endl;
        Sleep(1200);
    }

    return 0;
}
