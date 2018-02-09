#ifndef MODEL_GLOBAL_H
#define MODEL_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef MODEL_LIBRARY
    #define MODEL_API Q_DECL_EXPORT
#else
    #define MODEL_API Q_DECL_IMPORT
#endif

#endif
