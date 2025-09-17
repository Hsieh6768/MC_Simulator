#ifndef COMMAND_INPUT_H
#define COMMAND_INPUT_H

#include <string>
#include <map>

// 声明外部变量和函数
extern std::map<std::string, int> chineseCommands;
int convertChineseCommand(const std::string& input);

#endif
