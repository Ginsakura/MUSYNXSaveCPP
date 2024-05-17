#include "Functions.h"

#include <iostream>
#include <string>
#include <Windows.h>
#include <format>

//==================================================================
//函 数 名：SetSeed
//功能描述：初始化随机数种子
//输入参数：
//返 回 值：seed: unsigned
//==================================================================
unsigned SetSeed() {
	LARGE_INTEGER frequency;
	LARGE_INTEGER time;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&time);
	std::cout << "Random Engine Init...\n";
	std::cout << "Freq: " << frequency.QuadPart << " Hz, Time: " << time.QuadPart << " Cycle\n\n";
	isRandomInit = true;
	return (unsigned int)(time.QuadPart * 1000 / frequency.QuadPart);
}

//==================================================================
//函 数 名：Randint
//功能描述：随机整数
//输入参数：min: int, max: int
//返 回 值：number: int
//==================================================================
int Randint(int min = 0, int max = RAND_MAX) {
	if (!isRandomInit) srand(SetSeed());
	return rand() % (max - min) + min;
}

//==================================================================
//函 数 名：Random
//功能描述：随机浮点数
//输入参数：min: double, max:double
//返 回 值：number: double
//==================================================================
double Random(double min = 0, double max = RAND_MAX) {
	if (!isRandomInit) srand(SetSeed());
	return ((double)rand() / RAND_MAX) * (max - min) + min;
}

//==================================================================
//函 数 名：FgColor
//功能描述：设定控制台文字前景色(标准输出)
//输入参数：red: int, green: int, blue: int
//返 回 值：ANSI: string
//==================================================================
std::string FgColor(int r, int g, int b) {
	return std::format("\033[38;2;{};{};{}m", r, g, b);
}

//==================================================================
//函 数 名：BgColor
//功能描述：设定控制台文字背景色(标准输出)
//输入参数：red: int, green: int, blue: int
//返 回 值：ANSI: string
//==================================================================
std::string BgColor(int r, int g, int b) {
	return std::format("\033[48;2;{};{};{}m", r, g, b);
}

//==================================================================
//函 数 名：ResetColor
//功能描述：清除控制台文字前景背景色(标准输出)
//输入参数：
//返 回 值：ANSI: string
//==================================================================
std::string ResetColor() {
	return "\033[m";
}

//==================================================================
//函 数 名：QFgColor
//功能描述：设定控制台文字前景色(QtDebug输出)
//输入参数：red: int, green: int, blue: int
//返 回 值：ANSI: QString
//==================================================================
QString QFgColor(int r, int g, int b) {
	return QString("\033[38;2;%0;%1;%2m").arg(r).arg(g).arg(b);
}

//==================================================================
//函 数 名：QBgColor
//功能描述：设定控制台文字背景色(QtDebug输出)
//输入参数：red: int, green: int, blue: int
//返 回 值：ANSI: QString
//==================================================================
QString QBgColor(int r, int g, int b) {
	return QString("\033[48;2;%0;%1;%2m").arg(r).arg(g).arg(b);
}

//==================================================================
//函 数 名：QResetColor
//功能描述：清除控制台文字前景背景色(QtDebug输出)
//输入参数：
//返 回 值：ANSI: QString
//==================================================================
QString QResetColor() {
	return QString("\033[m");
}

//==================================================================
//函 数 名：GetScreenScale
//功能描述：获取系统DPI
//输入参数：
//返 回 值：DPI: double
//==================================================================
double GetScreenScale() {
	int screenW = ::GetSystemMetrics(SM_CXSCREEN);
	int screenH = ::GetSystemMetrics(SM_CYSCREEN);
	//std::cout << "screenW =" << screenW << "screenH=" << screenH << std::endl;
	//HWND hwd = ::GetDesktopWindow();
	HDC hdc = ::GetDC(::GetDesktopWindow());
	int width = ::GetDeviceCaps(hdc, DESKTOPHORZRES);
	int height = ::GetDeviceCaps(hdc, DESKTOPVERTRES);
	//std::cout << "width=" << width << "height=" << height << std::endl;
	double scale = (double)width / screenW;
	return scale;
}