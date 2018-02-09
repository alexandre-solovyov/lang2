
#ifndef STD_TENSE_H
#define STD_TENSE_H

#include <model/itense.h>
#include <model/grammarrule.h>
#include <QList>

class MODEL_API StdTense : public ITense
{
public:
    StdTense( const QString& );
    virtual ~StdTense();

    void Add( const QString& );

    virtual GrammarSet Forms( const QString& theWord ) const;

private:
    QList<GrammarRule> myRules;
};

#endif  // STD_TENSE_H
