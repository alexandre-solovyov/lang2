
#include <model/GrammarRule.h>
#include <model/GrammarSet.h>
#include <model/PrefixModel.h>
#include <model/Tools.h>

GrammarRule::GrammarRule( const QString& theRule )
{
    if( theRule.isEmpty() )
        return;

    static QRegExp PATTERN( "\\[(\\w+)\\] ([\\~\\@]?[\\w\\~\\.\\(\\)\\|]*) >> (.+)" );

    if( !PATTERN.exactMatch( theRule ) )
    {
        Tools::print( QString( "Not matched: " ) + theRule );
        return;
    }

    myGroup  = PATTERN.cap( 1 );
    myStart  = PATTERN.cap( 2 );
    myResult = PATTERN.cap( 3 ).split( "," );
    //Tools::print( "Matched: " + myStart );

    for( int i=0, n=myResult.size(); i<n; i++ )
        myResult[i] = myResult[i].trimmed();

    myParts = 0;
    myIsPrefix = myStart.contains( '@' );
    QString aRule = "^" + myStart + "$";
    foreach( QChar c, myStart )
        if( c=='~' || c=='@' || c=='.' || c=='(' )
            myParts++;

    aRule.replace( "@", "(\\w*)");
    aRule.replace( "~", "([\\w\\-]*)");
    aRule.replace( ".", "(.)");
    //Tools::print( aRule );

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

bool GrammarRule::Match( const QString& theWord, const PrefixModel* thePrefixModel ) const
{
    bool isOK = myRule.exactMatch( theWord );
    if( isOK && myIsPrefix && thePrefixModel )
    {
        QString aPrefix = myRule.cap( 1 );
        if( !aPrefix.isEmpty() )
        {
            //Tools::print( QString( "Match with prefix: %0 %1" ).arg( aPrefix ).arg( theWord ) );
            if( !thePrefixModel->Match(theWord, aPrefix) )
            {
                //Tools::print("Not match by prefix");
                return false;
            }
        }
    }
    return isOK;
}

GrammarSet GrammarRule::Forms( const QString& theWord, const PrefixModel* thePrefixModel ) const
{
    if( !Match( theWord, thePrefixModel ) )
        return GrammarSet();

    //Tools::print( QString( "Matched word: " ) + theWord );
    //for( int i=0; i<myParts; i++ )
    //    Tools::print( myRule.cap( i+1 ) );

    GrammarSet aResult(myResult);
    for( uint i=0; i<myParts; i++ )
    {
        QString aPlaceHolder = myRule.cap( i+1 );
        aResult.ReplaceNext( aPlaceHolder );
    }

    aResult.processSpecial();

    return aResult;
}

bool GrammarRule::Include( const GrammarRule& theRule ) const
{
    QString start = theRule.Start();
    QString var1 = start; var1.replace( "~", "" );
    QString var2 = start; var1.replace( "~", "%" );
    return Match( var1 ) && Match( var2 );
}
