#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(HITDELAY_LIB)
#  define HITDELAY_EXPORT Q_DECL_EXPORT
# else
#  define HITDELAY_EXPORT Q_DECL_IMPORT
# endif
#else
# define HITDELAY_EXPORT
#endif
