
#include <model/stdtense.h>
#include <model/grammarset.h>

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
