
#ifndef EG_FORMS_H
#define EG_FORMS_H

#include <model/eg_trans.h>
#include <QMap>

class Grammar;
class StdTense;

class MODEL_API EG_Forms : public EG_Trans
{
public:
    EG_Forms( Grammar*, bool isCopyTenses );
    virtual ~EG_Forms();

    virtual void Reset();
    virtual void Ignore( const QStringList& );
    virtual ListOfExercises Generate( const QString& theLine, const Context& theContext, bool& isOtherProduct ) const;
    virtual QString Type() const;

protected:
    void CopyTenses();
    void DeleteTenses();

private:
    Grammar* myGrammar;
    QMap<QString, StdTense*> myTenses;
    QStringList myIgnore;
    bool myIsCopyTenses;
};

#endif // EG_FORMS_H
