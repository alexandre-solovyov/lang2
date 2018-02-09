
#include <model/grammar.h>
#include <model/grammarset.h>
#include <model/itense.h>

Grammar::Grammar()
{
}

Grammar::~Grammar()
{
}

GrammarSet Grammar::Forms( const QString& theTense, const QString& theWord ) const
{
    if( myTenses.contains( theTense ) )
        return myTenses[theTense]->Forms( theWord );
    else
        return GrammarSet();
}
