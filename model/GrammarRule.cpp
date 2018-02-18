
#include <model/GrammarRule.h>
#include <model/GrammarSet.h>
#include <model/Tools.h>

GrammarRule::GrammarRule( const QString& theRule )
{
    QRegExp PATTERN( "\\[(\\w+)\\] (\\~?[\\w\\.]*) >> (.+)" );

    if( !PATTERN.exactMatch( theRule ) )
    {
        Tools::print( QString( "Not matched: " ) + theRule );
        return;
    }

    //printf( "Matched\n" );
    myGroup  = PATTERN.cap( 1 );
    myStart  = PATTERN.cap( 2 );
    myResult = PATTERN.cap( 3 ).split( "," );
    for( int i=0, n=myResult.size(); i<n; i++ )
        myResult[i] = myResult[i].trimmed();

    myParts = 0;
    QString aRule = "^" + myStart + "$";
    foreach( QChar c, myStart )
        if( c=='~' || c=='.' )
            myParts++;

    aRule.replace( "~", "(\\w*)");
    aRule.replace( ".", "(.)");

    myRule = QRegExp( aRule );
}

GrammarRule::~GrammarRule()
{
}

bool GrammarRule::IsSingle() const
{
    return !myStart.contains("~");
}

QString GrammarRule::Group() const
{
    return myGroup;
}

QString GrammarRule::Start() const
{
    return myStart;
}

GrammarSet GrammarRule::Result() const
{
    return myResult;
}

bool GrammarRule::Match( const QString& theWord ) const
{
    return myRule.exactMatch( theWord );
}

GrammarSet GrammarRule::Forms( const QString& theWord ) const
{
    if( !Match( theWord ) )
        return GrammarSet();

    GrammarSet aResult(myResult);
    for( int i=0; i<myParts; i++ )
    {
        QString aPlaceHolder = myRule.cap( i+1 );
        aResult.ReplaceNext( aPlaceHolder );
    }

    return aResult;
}

bool GrammarRule::Include( const GrammarRule& theRule ) const
{
    QString start = theRule.Start();
    QString var1 = start; var1.replace( "~", "" );
    QString var2 = start; var1.replace( "~", "%" );
    return Match( var1 ) && Match( var2 );
}
