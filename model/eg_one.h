
#ifndef EG_ONE_H
#define EG_ONE_H

#include "igenerator.h"

class MODEL_API EG_One : public IGenerator
{
public:
    EG_One();
    virtual ~EG_One();

    virtual QList<Exercise> Generate( const QString& theLine, const Context& theContext ) const;
};

#endif // IGENERATOR_H
