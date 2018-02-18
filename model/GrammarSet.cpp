
#include <model/GrammarSet.h>
#include <model/Tools.h>

GrammarSet::GrammarSet( const QStringList& theList )
    : QStringList( theList )
{
}

GrammarSet::GrammarSet( const QString& theValue, int theSize )
{
    for( int i=0; i<theSize; i++ )
        append( theValue );
}

GrammarSet::GrammarSet( const QString& theItems, const QString& theSep )
{
    *this = theItems.split( theSep, QString::SkipEmptyParts );
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
         aSet.append( sum( arg1, arg2 ) );
    }
    return aSet;
}

GrammarSet GrammarSet::operator + ( const QString& theValue ) const
{
    return operator + ( GrammarSet( theValue, size() ) );
}

GrammarSet operator + ( const QString& theValue, const GrammarSet& theSet )
{
    return GrammarSet( theValue, theSet.size() ) + theSet;
}

GrammarSet GrammarSet::operator + ( const char* theValue ) const
{
    return operator + ( GrammarSet( theValue, size() ) );
}

GrammarSet GrammarSet::operator * ( const GrammarSet& theSet ) const
{
    GrammarSet aSet;
    for( int i=0, n=size(); i<n; i++ )
        for( int j=0, m=theSet.size(); j<m; j++ )
        {
             QString arg1 = this->operator [](i);
             QString arg2 = theSet.operator [](j);
             aSet.append( sum( arg1, arg2 ) );
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

void GrammarSet::ReplaceNext( const QString& theReplace )
{
    for( int i=0, n=size(); i<n; i++ )
    {
        QString& anItem = operator[]( i );
        for( int j=0, m=anItem.size(); j<m; j++ )
        {
            if( anItem[j]=='~' || anItem[j]=='.' )
            {
                anItem.replace( j, 1, theReplace );
                break;
            }
        }
    }
}

QString GrammarSet::sum( const QString& theArg1, const QString& theArg2 ) const
{
    QString res = theArg1 + theArg2;
    int q = 0;
    while( ( q = res.indexOf('#') ) >= 0 )
    {
        if( q==0 )
            res.remove( q, 1 );
        else
            res.remove( q-1, 2 );
    }
    return res;
}
