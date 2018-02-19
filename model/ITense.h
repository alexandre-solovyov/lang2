
#ifndef ITENSE_H
#define ITENSE_H

#include <model/model_global.h>
#include <QString>

class Grammar;
class GrammarSet;

/**
  @class ITense
  @brief The interface for grammatical tenses
*/
class MODEL_API ITense
{
public:
    ITense( const QString&, Grammar* );
    virtual ~ITense();

    QString Name() const;
    Grammar* grammar() const;
    void setGrammar( Grammar* );

    virtual bool Unite( ITense* );
    virtual GrammarSet Forms( const QString& theWord ) const = 0;

private:
    QString myName;         ///< the tense's name
    Grammar* myGrammar;     ///< the associated grammar
};

#endif // ITENSE_H
