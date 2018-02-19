
#ifndef TOOLS_H
#define TOOLS_H

#include <model/model_global.h>
#include <QString>

class MODEL_API Tools
{
public:
    static QString normalize( const QString& );
    static void    print( const QString&, bool isEndOfLine = true );
    static bool    startsWithDigit( const QString& );
    static QChar   toLatin1( const QChar& );
    static bool    isVowel( const QChar&, const QString& theIgnore = "" );
    static bool    isConsonant( const QChar&, const QString& theIgnore = "" );
};

#endif // STATISTICS_H
