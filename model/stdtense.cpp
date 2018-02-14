
#include <model/stdtense.h>
#include <model/grammarrule.h>
#include <model/grammarset.h>

StdTense::StdTense( const QString& theName, Grammar* theGrammar )
    : ITense( theName, theGrammar )
{
}

StdTense::~StdTense()
{
}

GrammarRule StdTense::Add( const QString& theRule )
{
    GrammarRule gr( QString( "[%0] %1").arg( Name() ).arg( theRule ) );
    myRules.append( gr );
    return gr;
}

GrammarSet StdTense::Forms( const QString& theWord ) const
{
    foreach( const GrammarRule& aRule, myRules )
    {
        GrammarSet gs = aRule.Forms( theWord );
        if( !gs.empty() )
            return gs;
    }
    return GrammarSet();
}
