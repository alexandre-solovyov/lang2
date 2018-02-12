
#include <model/deptense.h>
#include <model/grammar.h>

DepTense::DepTense( const QString& theName, Grammar* theGrammar, const QString& theTense, uint theForm, const GrammarSet& theEndings )
    : ITense( theName, theGrammar ),
      myTense( theTense ),
      myForm( theForm ),
      myEndings( theEndings )
{
}

DepTense::~DepTense()
{
}

GrammarSet DepTense::Forms( const QString& theWord ) const
{
    if( myForm>=0 )
    {
        GrammarSet forms = grammar()->Forms( myTense, theWord );
        GrammarSet forms1;
        forms1.append( forms[myForm] );
        return forms1 * myEndings;
    }
    else
        return grammar()->Forms( myTense, theWord ) + myEndings;

    return GrammarSet();
}
