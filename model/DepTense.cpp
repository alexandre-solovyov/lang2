
#include <model/DepTense.h>
#include <model/Grammar.h>

/**
  @brief Constructor
  @param theName the dependent tense's name
  @param theGrammar the associated grammar
  @param theTense the source tense
  @param theForm the source form (-1 means all forms)
  @param theEndings the list of new endings
*/
DepTense::DepTense( const QString& theName, Grammar* theGrammar,
                    const QString& theTense, int theForm,
                    const GrammarSet& theEndings )
    : ITense( theName, theGrammar ),
      myTense( theTense ),
      myForm( theForm ),
      myEndings( theEndings )
{
}

/**
  @brief Destructor
*/
DepTense::~DepTense()
{
}

/**
*/
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
