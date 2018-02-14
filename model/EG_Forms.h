
#ifndef EG_FORMS_H
#define EG_FORMS_H

#include <model/eg_trans.h>

class Grammar;

class MODEL_API EG_Forms : public EG_Trans
{
public:
    EG_Forms( Grammar* );
    virtual ~EG_Forms();

    virtual void Reset();
    virtual ListOfExercises Generate( const QString& theLine, const Context& theContext, bool& isOtherProduct ) const;
    virtual QString Type() const;

private:
    Grammar* myGrammar;
    QStringList myTenses;
};

#endif // EG_FORMS_H
