#ifndef KERNEL_GLOBAL_H
#define KERNEL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(KERNEL_LIBRARY)
#  define KERNEL_EXPORT Q_DECL_EXPORT
#else
#  define KERNEL_EXPORT Q_DECL_IMPORT
#endif

#endif // KERNEL_GLOBAL_H
