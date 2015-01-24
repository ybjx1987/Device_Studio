#ifndef SHAREDLIBGLOBAL_H
#define SHAREDLIBGLOBAL_H

#include <QtCore/qglobal.h>

#if defined(KERNEL_LIBRARY)
#  define KERNEL_EXPORT Q_DECL_EXPORT
#else
#  define KERNEL_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBGLOBAL_H
