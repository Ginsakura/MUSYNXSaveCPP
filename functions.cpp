#include "functions.h"

#include <iostream>
#include <string>
#include <Windows.h>
#include <format>

unsigned SetSeed() {
	LARGE_INTEGER frequency;
	LARGE_INTEGER time;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&time);
	printf("Random Engine Init...\n");
	printf("Freq: %lld Hz, Time: %lld Cycle\n\n", frequency.QuadPart, time.QuadPart);
	isRandomInit = true;
	return (unsigned int)(time.QuadPart * 1000 / frequency.QuadPart);
}
int Randint(int low = 0, int high = RAND_MAX) {
	if (!isRandomInit) srand(SetSeed());
	return rand() % (high - low) + low;
}
double Random(double low = 0, double high = RAND_MAX) {
	if (!isRandomInit) srand(SetSeed());
	return ((double)rand() / RAND_MAX) * (high - low) + low;
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
	QString s = "\033[38;2;%1;%2;%3m";
	return s.arg(r).arg(g).arg(b);
}
QString QBgColor(int r, int g, int b) {
	QString s = "\033[48;2;%1;%2;%3m";
	return s.arg(r).arg(g).arg(b);
}
QString QResetColor() {
	QString s = "\033[m";
	return s;
}