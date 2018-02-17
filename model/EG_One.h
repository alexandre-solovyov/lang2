
#ifndef EG_ONE_H
#define EG_ONE_H

#include <model/IGenerator.h>

class MODEL_API EG_One : public IGenerator
{
public:
    EG_One();
    virtual ~EG_One();

    virtual void Reset();
    virtual void Ignore( const QStringList& );
    virtual ListOfExercises Generate( const QString& theLine, const Context& theContext, bool& isOtherProduct ) const;
    virtual QString Type() const;
};

#endif // EG_ONE_H
