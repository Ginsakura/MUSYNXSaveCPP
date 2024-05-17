#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SQL_LIB)
#  define SQL_EXPORT Q_DECL_EXPORT
# else
#  define SQL_EXPORT Q_DECL_IMPORT
# endif
#else
# define SQL_EXPORT
#endif
