
#include <model/GrammarSet.h>
#include <model/Tools.h>

/**
  @brief Constructor (list of values)
  @param theList the list of values
*/
GrammarSet::GrammarSet( const QStringList& theList )
    : QStringList( theList )
{
}

/**
  @brief Constructor (repeated value)
  @param theValue the value to repeat
  @param theSize the count of repeats
*/
GrammarSet::GrammarSet( const QString& theValue, int theSize )
{
    for( int i=0; i<theSize; i++ )
        append( theValue );
}

/**
  @brief Constructor (split string)
  @param theItems the string to split
  @param theSep the separator
*/
GrammarSet::GrammarSet( const QString& theItems, const QString& theSep )
{
    *this = theItems.split( theSep, QString::SkipEmptyParts );
}

/**
  @brief Convert grammar set to string
  @return the result string
*/
QString GrammarSet::toString() const
{
    return join( ", " );
}

/**
  @brief Sum of corresponding forms
  @param theSet another grammar set for sum
  @return the result grammar set
*/
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

/**
  @brief Sum of forms with one given form
  @param theValue the fixed form for sum
  @return the result grammar set
*/
GrammarSet GrammarSet::operator + ( const QString& theValue ) const
{
    return operator + ( GrammarSet( theValue, size() ) );
}

/**
  @brief Sum of one given form with other forms
  @param theValue the fixed form for sum
  @param theSet the other forms for sum
  @return the result grammar set
*/
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

void replaceIn( QString& theItem, const QString& theReplace )
{
    for( int j=0, m=theItem.size(); j<m; j++ )
    {
        if( theItem[j]=='~' || theItem[j]=='.' )
        {
            theItem.replace( j, 1, theReplace );
            break;
        }
    }
}

void GrammarSet::ReplaceNext( const QString& theReplace )
{
    for( int i=0, n=size(); i<n; i++ )
    {
        QString& anItem = operator[]( i );
        if( anItem.contains('|') )
        {
            QStringList items = anItem.split("|");
            for( int j=0, m=items.size(); j<m; j++)
                replaceIn( items[j], theReplace );
            anItem = items.join('|');
        }
        else
            replaceIn( anItem, theReplace );
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

void GrammarSet::processSpecial()
{
    for( int i=0, n=size(); i<n; i++ )
    {
        QString& anItem = operator[]( i );
        int ind;
        while( ( ind = anItem.indexOf( '&') ) >= 0 )
        {
            if( ind==0 )
                anItem.remove( ind, 1 );
            else
                anItem[ind] = anItem[ind-1]; // the sign '&' means duplication of previous letter
        }
    }
}
