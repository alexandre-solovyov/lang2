
#ifndef ITENSE_H
#define ITENSE_H

#include <model/model_global.h>
#include <QString>

class Grammar;
class GrammarSet;

class MODEL_API ITense
{
public:
    ITense( const QString&, Grammar* );
    virtual ~ITense();

    QString Name() const;
    Grammar* grammar() const;

    virtual GrammarSet Forms( const QString& theWord ) const = 0;

private:
    QString myName;
    Grammar* myGrammar;
};

#endif // ITENSE_H
