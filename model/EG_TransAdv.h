
#ifndef EG_TRANS_ADV_H
#define EG_TRANS_ADV_H

#include <model/IGenerator.h>

class MODEL_API EG_TransAdv : public IGenerator
{
public:
    EG_TransAdv();
    virtual ~EG_TransAdv();

    virtual void Reset();
    virtual void Ignore( const QStringList& );
    virtual ListOfExercises Generate( const QString& theLine, const Context& theContext, bool& isOtherProduct ) const;
    virtual QString Type() const;
};

#endif // EG_TRANS_ADV_H
