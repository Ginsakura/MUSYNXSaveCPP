#pragma once

#include <functions_global.h>
#include <QString>

static bool isRandomInit = false;
FUNCTIONS_EXPORT unsigned SetSeed(void);
FUNCTIONS_EXPORT int Randint(int, int);
FUNCTIONS_EXPORT double Random(double, double);
FUNCTIONS_EXPORT double GetScreenScale();
FUNCTIONS_EXPORT std::string FgColor(int, int, int);
FUNCTIONS_EXPORT std::string BgColor(int, int, int);
FUNCTIONS_EXPORT std::string ResetColor(void);
FUNCTIONS_EXPORT QString QFgColor(int r, int g, int b);
FUNCTIONS_EXPORT QString QBgColor(int r, int g, int b);
FUNCTIONS_EXPORT QString QResetColor();