
#ifndef EG_FORMS_H
#define EG_FORMS_H

#include <model/EG_Trans.h>
#include <QMap>

class Grammar;
class StdTense;

/**
  @class EG_Forms
  @brief The implementation of the forms generator
*/
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
    Grammar*                 myGrammar;      ///< the associated grammar
    QMap<QString, StdTense*> myTenses;       ///< the map of temporary (internal) tenses
    QStringList              myIgnore;       ///< the ignore list of words (not to apply form generation)
    bool                     myIsCopyTenses; ///< whether the tenses should be copied to grammar on reset
};

#endif // EG_FORMS_H
