
#include <model/grammar.h>
#include <model/grammarset.h>
#include <model/itense.h>

Grammar::Grammar( bool isOwner )
    : myIsOwner( isOwner )
{
}

Grammar::~Grammar()
{
    if( myIsOwner )
    {
        QMap<QString, ITense*>::const_iterator it = myTenses.begin(), last = myTenses.end();
        for( ; it!=last; it++ )
            delete it.value();
    }
}

void Grammar::Add( ITense* theTense )
{
    if( theTense )
        myTenses[theTense->Name()] = theTense;
}

GrammarSet Grammar::Forms( const QString& theTense, const QString& theWord ) const
{
    if( myTenses.contains( theTense ) )
        return myTenses[theTense]->Forms( theWord );
    else
        return GrammarSet();
}
