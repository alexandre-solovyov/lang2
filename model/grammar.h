
#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <model/model_global.h>
#include <model/grammarrule.h>
#include <QMap>

class GrammarSet;
class ITense;

class MODEL_API Grammar
{
public:
    Grammar();
    ~Grammar();

    GrammarSet Forms( const QString& theTense, const QString& theWord ) const;

private:
    QMap<QString, ITense*> myTenses;
};

#endif // GRAMMAR_H
