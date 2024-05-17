#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(DIFFICULTYSCOREANALYZE_LIB)
#  define DIFFICULTYSCOREANALYZE_EXPORT Q_DECL_EXPORT
# else
#  define DIFFICULTYSCOREANALYZE_EXPORT
# endif
#else
# define DIFFICULTYSCOREANALYZE_EXPORT
#endif
