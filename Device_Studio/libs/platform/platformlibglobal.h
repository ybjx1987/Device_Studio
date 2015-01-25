#ifndef SHAREDLIBGLOBAL_H
#define SHAREDLIBGLOBAL_H

#include <QtCore/qglobal.h>

#ifdef PLATFORM_LIBRARY
#  define PLATFORM_EXPORT Q_DECL_EXPORT
#else
#  define PLATFORM_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBGLOBAL_H
