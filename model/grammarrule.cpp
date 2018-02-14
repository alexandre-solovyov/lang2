
#include <model/grammarrule.h>
#include <model/grammarset.h>

GrammarRule::GrammarRule( const QString& theRule )
{
    QRegExp PATTERN( "\\[(\\w+)\\] (\\~?\\w*) >> (.+)" );

    if( !PATTERN.exactMatch( theRule ) )
    {
        //printf( "Not matched\n" );
        return;
    }

    //printf( "Matched\n" );
    myGroup  = PATTERN.cap( 1 );
    myStart  = PATTERN.cap( 2 );
    myResult = PATTERN.cap( 3 ).split( "," );
    for( int i=0, n=myResult.size(); i<n; i++ )
        myResult[i] = myResult[i].trimmed();

    QString aRule = "^" + myStart + "$";
    aRule.replace( "~", "(\\w*)");

    myRule = QRegExp( aRule );
}

GrammarRule::~GrammarRule()
{
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

    QString aBase = myRule.cap( 1 );
    return GrammarSet(myResult).Replaced( "~", aBase );
}
