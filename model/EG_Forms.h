
#ifndef EG_FORMS_H
#define EG_FORMS_H

#include <model/eg_trans.h>
#include <QMap>

class Grammar;
class StdTense;

class MODEL_API EG_Forms : public EG_Trans
{
public:
    EG_Forms( Grammar* );
    virtual ~EG_Forms();

    virtual void Reset();
    virtual void Ignore( const QStringList& );
    virtual ListOfExercises Generate( const QString& theLine, const Context& theContext, bool& isOtherProduct ) const;
    virtual QString Type() const;

    void CopyTenses();

private:
    Grammar* myGrammar;
    QMap<QString, StdTense*> myTenses;
    QStringList myIgnore;
};

#endif // EG_FORMS_H
