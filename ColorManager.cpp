#include "ColorManager.h"

void ColorManager::COLOR_PRINT(const std::string& str, int color)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color);
    std::cout << str;
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | WHITE);
}
