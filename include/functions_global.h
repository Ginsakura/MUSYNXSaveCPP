#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(FUNCTIONS_LIB)
#  define FUNCTIONS_EXPORT Q_DECL_EXPORT
# else
#  define FUNCTIONS_EXPORT Q_DECL_IMPORT
# endif
#else
# define FUNCTIONS_EXPORT
#endif
