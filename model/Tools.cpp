
#include <model/Tools.h>
#ifdef WIN32
  #include <windows.h>
#else
  #include <stdio.h>
#endif
#include <QStringList>
#include <QMap>
#include <QDebug>

class InvMap
{
public:
    void Add( const QString& key, const QString& value )
    {
        if( value.isEmpty() )
            return;
        myDirect.insert( key, value[0] );
        myInverse.insert( value[0].unicode(), key );
    }

    bool empty() const
    {
        return myDirect.empty();
    }

    QMap<QString, QChar>::const_iterator begin() const
    {
        return myDirect.begin();
    }

    QMap<QString, QChar>::const_iterator end() const
    {
        return myDirect.end();
    }

    QString inverse( const QChar& c ) const
    {
        if( myInverse.contains(c) )
            return myInverse[c];
        else
            return "";
    }

private:
    QMap<QString, QChar>  myDirect;
    QMap<QChar, QString>  myInverse;
};

InvMap ND;

void fillND()
{
    ND.Add("a\\", "à");
    ND.Add("a`",  "à");
    ND.Add("a^",  "â");
    ND.Add("a+",  "æ");
    ND.Add("c+",  "ç");
    ND.Add("e/",  "é");
    ND.Add("e'",  "é");
    ND.Add("e\\", "è");
    ND.Add("e`",  "è");
    ND.Add("e^",  "ê");
    ND.Add("e:",  "ë");
    ND.Add("i:",  "ï");
    ND.Add("i^",  "î");
    ND.Add("o^",  "ô");
    ND.Add("o+",  "œ");
    ND.Add("u\\", "ù");
    ND.Add("u`",  "ù");
    ND.Add("u^",  "û");
    ND.Add("u:",  "ü");
    ND.Add("y:",  "ÿ");
}

/**
  @brief Normalize the given text
  @param theText the text to normalize
  @return the normalized text
*/
QString Tools::normalize( const QString& theText )
{
    if( ND.empty() )
        fillND();

    QString aText = theText;
    QMap<QString, QChar>::const_iterator it = ND.begin(), last = ND.end();
    for( ; it!=last; ++it )
        aText.replace( it.key(), it.value() );
    return aText;
}

/**
  @brief Print the given text in the unicode console
  @param theText the text to print
  @param isEndOfLine if the end-of-line should be printed
*/
void Tools::print( const QString& theText, bool isEndOfLine )
{
    QString aText = theText + ( isEndOfLine ? "\n" : "" );
#ifdef WIN32
    WriteConsoleW( GetStdHandle(STD_OUTPUT_HANDLE), aText.utf16(), aText.size(), NULL, NULL );
    qDebug() << theText;
#else
    //TODO: unicode console on Linux
    printf( "%s", aText.toStdString().c_str() );
#endif
}

/**
  @brief Check if the text starts with digit
  @param theText the text to check
  @return whether the text starts with digit
*/
bool Tools::startsWithDigit( const QString& theText )
{
    if( theText.isEmpty() )
        return false;
    else
        return theText[0].isDigit();
}

QChar Tools::toLatin1( const QChar& c )
{
    if( ND.empty() )
        fillND();

    QString q = ND.inverse( c );
    if( q.isEmpty() )
        return c;
    else
        return q[0];
}

bool Tools::isVowel( const QChar& c, const QString& ignore )
{
    static QString VOWELS( "aeiouy");
    QChar cl = toLatin1(c);
    return VOWELS.contains( cl ) && !ignore.contains( cl );
}

bool Tools::isConsonant( const QChar& c, const QString& ignore )
{
    static QString CONSONANTS( "bcdfghjklmnpqrstvwxz");
    QChar cl = toLatin1(c);
    return CONSONANTS.contains( cl ) && !ignore.contains( cl );
}

QString Tools::simplifySpaces( const QString& theLine )
{
    QString aLine = theLine.split( " ", QString::SkipEmptyParts ).join( " " );

    int anIndex = aLine.indexOf("//");
    if( anIndex>=0 && aLine.mid(anIndex, 3)!="//!" )
        aLine = aLine.left( anIndex ).trimmed();

    anIndex  = aLine.indexOf("#");
    if( anIndex>=0 )
        aLine = aLine.left( anIndex ).trimmed();

    return aLine;
}
