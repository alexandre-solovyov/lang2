
#include <model/tools.h>
#include <windows.h>
#include <QMap>

QString Tools::normalize( const QString& theText )
{
    static QMap<QString, QString> ND;

    if( ND.empty() )
    {
        ND["a\\"] = "à";
        ND["a`"] = "à";
        ND["a^"] = "â";
        ND["a+"] = "æ";
        ND["c+"] = "ç";
        ND["e/"] = "é";
        ND["e'"] = "é";
        ND["e\\"] = "è";
        ND["e`"] = "è";
        ND["e^"] = "ê";
        ND["e:"] = "ë";
        ND["i:"] = "ï";
        ND["i^"] = "î";
        ND["o^"] = "ô";
        ND["o+"] = "œ";
        ND["u\\"] = "ù";
        ND["u`"] = "ù";
        ND["u^"] = "û";
        ND["u:"] = "ü";
        ND["y:"] = "ÿ";
    }

    QString aText = theText;
    QMap<QString, QString>::const_iterator it = ND.begin(), last = ND.end();
    for( ; it!=last; it++ )
        aText.replace( it.key(), it.value() );
    return aText;
}

void Tools::print( const QString& theText, bool isEndOfLine )
{
    QString aText = theText + ( isEndOfLine ? "\n" : "" );
    WriteConsoleW( GetStdHandle(STD_OUTPUT_HANDLE), aText.utf16(), aText.size(), NULL, NULL );
}

bool Tools::startsWithDigit( const QString& theText )
{
    if( theText.isEmpty() )
        return false;
    else
        return theText[0].isDigit();
}
