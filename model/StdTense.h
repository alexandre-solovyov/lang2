
#ifndef STD_TENSE_H
#define STD_TENSE_H

#include <model/ITense.h>
#include <model/GrammarRule.h>
#include <QList>

class MODEL_API StdTense : public ITense
{
public:
    StdTense( const QString&, Grammar* );
    virtual ~StdTense();

    GrammarRule Add( const QString& );

    virtual bool Unite( ITense* );
    virtual GrammarSet Forms( const QString& theWord ) const;

private:
    QList<GrammarRule> myRules;
};

#endif  // STD_TENSE_H
