// ²Î¿¼£ºhttps://blog.csdn.net/qq_42885747/article/details/103835671
#ifndef COLOR_MANAGER
#define COLOR_MANAGER

#include <iostream>
#include <string>
#include <stdio.h>
#include <windows.h>

enum Color {
	BLACK,  // 0 ºÚÉ«
	LIGHT_BLUE,  // 1 µ­À¶
	LIGHT_GREEN,  // 2 µ­ÂÌ
	LAKE_BLUE,  // 3 ºþÀ¶
	LIGHT_RED,  // 4 µ­ºì
	PURPLE,  // 5 ×ÏÉ«
	YELLOW,  // 6 »ÆÉ«
	WHITE,  // 7 °×É«
	GREY,  // 8 »ÒÉ«
	BLUE,  // 9 À¶É«
	GREEN,  // 10 ÂÌÉ«
	LIGHT_PALE_GREEN,  // 11 µ­Ç³ÂÌ
	RED,  // 12 ºìÉ«
	LAVENDER,  // 13 µ­×Ï
	PALE_YELLOW,  // 14 µ­»Æ
	BRIGHT_WHITE  // 15 ÁÁ°×
};

class ColorManager {
public:
	static void COLOR_PRINT(const std::string& str, int color);
};

#endif
