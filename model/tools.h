
#ifndef TOOLS_H
#define TOOLS_H

#include <model/model_global.h>

class MODEL_API Tools
{
public:
    static QString normalize( const QString& );
    static void print( const QString&, bool isEndOfLine = true );
};

#endif // STATISTICS_H
