#ifndef QARTNET_GLOBAL_H
#define QARTNET_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QARTNET_LIBRARY)
#  define QARTNETSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QARTNETSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QARTNET_GLOBAL_H
