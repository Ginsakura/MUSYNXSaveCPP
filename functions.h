#pragma once
#include <QString>

static bool isRandomInit = false;
unsigned SetSeed(void);
int Randint(int, int);
double Random(double, double);
//std::string FgColor(int, int, int);
//std::string FgColor(int, int, int);
//std::string ResetColor(void);
QString QFgColor(int r, int g, int b);
QString QBgColor(int r, int g, int b);
QString QResetColor();