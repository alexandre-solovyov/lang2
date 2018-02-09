
#include <grammar.h>

GrammarSet::GrammarSet( const QStringList& theList )
    : QStringList( theList )
{
}

GrammarSet::GrammarSet( const QString& theValue, int theSize )
{
    for( int i=0; i<theSize; i++ )
        append( theValue );
}

QString GrammarSet::toString() const
{
    return join( ", " );
}

GrammarSet GrammarSet::operator + ( const GrammarSet& theSet ) const
{
    GrammarSet aSet;
    for( int i=0, n=qMax(size(), theSet.size()); i<n; i++ )
    {
         QString arg1 = i<size() ? this->operator [](i) : "";
         QString arg2 = i<theSet.size() ? theSet.operator [](i) : "";
         aSet.append( arg1+arg2 );
    }
    return aSet;
}

GrammarSet GrammarSet::operator + ( const QString& theValue ) const
{
    return operator + ( GrammarSet( theValue, size() ) );
}

GrammarSet GrammarSet::operator + ( const char* theValue ) const
{
    return operator + ( GrammarSet( theValue, size() ) );
}

GrammarSet GrammarSet::operator * ( const GrammarSet& theSet ) const
{
    GrammarSet aSet;
    for( int i=0, n=size(); i<n; i++ )
        for( int j=0, m=size(); j<m; j++ )
    {
         QString arg1 = this->operator [](i);
         QString arg2 = theSet.operator [](j);
         aSet.append( arg1+arg2 );
    }
    return aSet;
}

GrammarSet GrammarSet::Replaced( const QString& theStrToFind, const QString& theReplace )
{
    GrammarSet aResult;
    foreach( QString anItem, *this )
    {
        anItem.replace( theStrToFind, theReplace );
        aResult.append( anItem );
    }
    return aResult;
}



GrammarRule::GrammarRule( const QString& theRule )
{
    QRegExp PATTERN( "\\[(\\w+)\\] (\\~?\\w+) >> (.+)" );

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


Grammar::Grammar()
{
}

Grammar::~Grammar()
{
}
