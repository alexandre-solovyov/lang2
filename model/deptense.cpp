
#include <model/deptense.h>

DepTense::DepTense( const QString& theName, const QString& theTense, uint theForm, const GrammarSet& theEndings )
    : ITense( theName ),
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
    return GrammarSet();
}
