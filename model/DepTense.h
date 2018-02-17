
#ifndef DEP_TENSE_H
#define DEP_TENSE_H

#include <model/ITense.h>
#include <model/GrammarSet.h>

class MODEL_API DepTense : public ITense
{
public:
    DepTense( const QString& theName, Grammar* theGrammar, const QString& theTense, int theForm, const GrammarSet& theEndings );
    virtual ~DepTense();

    virtual GrammarSet Forms( const QString& theWord ) const;

private:
    QString myTense;
    int myForm;
    GrammarSet myEndings;
};

#endif  // DEP_TENSE_H
