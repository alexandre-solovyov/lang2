
#ifndef DEP_TENSE_H
#define DEP_TENSE_H

#include <model/itense.h>
#include <model/grammarset.h>

class MODEL_API DepTense : public ITense
{
public:
    DepTense( const QString& theName, Grammar* theGrammar, const QString& theTense, uint theForm, const GrammarSet& theEndings );
    virtual ~DepTense();

    virtual GrammarSet Forms( const QString& theWord ) const;

private:
    QString myTense;
    uint myForm;
    GrammarSet myEndings;
};

#endif  // DEP_TENSE_H
