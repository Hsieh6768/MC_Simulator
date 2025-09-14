#include <iostream>
#include <windows.h>
#include "Command.h"
#include "Battle.h"
#include "Map.h"
#include "Player.h"
#include "Monster.h"
#include "ColorManager.h"

using namespace std;

int main() {
    while (true) {
        Player player;
        Map map;
        Command command(player, map);

        // 进入游戏首页
        bool in_game = false;
        while (!in_game) {
            command.displayMainMenu();
            int game_choice;

            if (!(cin >> game_choice)) {
                // 清除错误状态并清空输入缓冲区
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                system("cls");
                cout << "无效的选择，请重新输入！" << endl;
                Sleep(1200);
                continue;
            }

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
            system("cls");
            // 显示当前位置信息
            map.displayCurrentPosition();

            // 显示游戏菜单
            command.displayGameMenu();
            int operation_choice;

            if (!(cin >> operation_choice)) {
                // 清除错误状态并清空输入缓冲区
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                system("cls");
                cout << "无效的选择，请重新输入！" << endl;
                Sleep(1200);
                continue;
            }

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
            case 9:
                system("cls");
                cout << "返回游戏首页。" << endl;
                Sleep(1200);
                game_running = false;
                break;
            case 10:
                system("cls");
                cout << "播放终末之诗。" << endl;
                Sleep(1200);
                command.gameOver();
                break;
            default:
                system("cls");
                cout << "无效的选择，请重新输入！" << endl;
                Sleep(1200);
            }

            // 检查玩家是否死亡
            if (player.getHealthCur() <= 0) {
                bool player_dead = true;
                while (player_dead) {
                    system("cls");
                    cout << "\n========================================" << endl;
                    cout << "            你已被击败！" << endl;
                    cout << "========================================" << endl;
                    cout << "1. 回到战斗前" << endl;
                    cout << "2. 退回到游戏首页" << endl;
                    cout << "请选择: ";

                    int death_choice = 0;

                    if (!(cin >> death_choice)) {
                        // 清除错误状态并清空输入缓冲区
                        cin.clear();
                        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                        system("cls");
                        cout << "无效的选择，请重新输入！" << endl;
                        Sleep(1200);
                        continue;
                    }

                    if (death_choice == 1) {
                        if (command.loadGame("autosave.txt")) {
                            system("cls");
                            cout << "已加载，回到战斗前状态。" << endl;
                            Sleep(1200);
                            player_dead = false;
                        }
                        else {
                            system("cls");
                            cout << "加载失败！返回游戏首页。" << endl;
                            Sleep(1200);
                            player_dead = false;
                            game_running = false;
                        }
                    }
                    else if (death_choice == 2) {
                        system("cls");
                        cout << "返回游戏首页..." << endl;
                        Sleep(1200);
                        player_dead = false;
                        game_running = false;
                    }
                    else {
                        system("cls");
                        cout << "无效的选择，请重新输入！" << endl;
                        Sleep(1200);
                    }
                }
            }
        }
    }

    return 0;
}
