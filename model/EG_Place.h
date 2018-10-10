
#ifndef EG_PLACE_H
#define EG_PLACE_H

#include <model/IGenerator.h>

class MODEL_API EG_Place : public IGenerator
{
public:
    EG_Place();
    virtual ~EG_Place();

    virtual void Reset();
    virtual void Ignore( const QStringList& );
    virtual ListOfExercises Generate( const QString& theLine, const Context& theContext, bool& isOtherProduct ) const;
    virtual QString Type() const;
};

#endif // EG_PLACE_H
