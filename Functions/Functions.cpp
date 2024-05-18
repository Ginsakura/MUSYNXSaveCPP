#include "Functions.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <Windows.h>
#include <format>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QSettings>

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

int Randint(int min = 0, int max = RAND_MAX) {
	if (!isRandomInit) srand(SetSeed());
	return rand() % (max - min) + min;
}

double Random(double min = 0, double max = RAND_MAX) {
	if (!isRandomInit) srand(SetSeed());
	return ((double)rand() / RAND_MAX) * (max - min) + min;
}

std::string FgColor(int r, int g, int b) {
	return std::format("\033[38;2;{};{};{}m", r, g, b);
}

std::string BgColor(int r, int g, int b) {
	return std::format("\033[48;2;{};{};{}m", r, g, b);
}

std::string ResetColor() {
	return "\033[m";
}

QString QFgColor(int r, int g, int b) {
	return QString("\033[38;2;%0;%1;%2m").arg(r).arg(g).arg(b);
}

QString QBgColor(int r, int g, int b) {
	return QString("\033[48;2;%0;%1;%2m").arg(r).arg(g).arg(b);
}

QString QResetColor() {
	return QString("\033[m");
}

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

bool isFileExists(std::string& name) {
	std::ifstream ifs(name.c_str());
	return ifs.good();
}

std::string SearchMainExecPath() {
	std::string path = "";
	//replace(path.begin(), path.end(), '\\', '_');
	return path;
}

Config* LoadConfig() {
	Config* config = new Config();
	return config;
}

bool WriteConfig(Config* config) {
	return false;
}

void ChangeConsoleStyle(Config* config) {
	// 打开注册表项: "HKEY_CURRENT_USER\\Console\\musynx.exe"
	QSettings setting(QString("HKEY_CURRENT_USER\\Console\\musynx.exe"), QSettings::NativeFormat);
	// 写入注册表键值对
	setting.setValue("CodePage", 65001);
	setting.setValue("WindowSize", 262174);
	setting.setValue("WindowAlpha", (config->ConsoleAlpha * 255 / 100));
	setting.setValue("FaceName", config->ConsoleFont);
	setting.setValue("FontSize", config->ConsoleFontSize);
	setting.setValue("CursorSize", 32);
	//setting.remove("delete");
}