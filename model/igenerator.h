
#ifndef IGENERATOR_H
#define IGENERATOR_H

#include <QStringList>
#include "exercise.h"
#include "model_global.h"

class MODEL_API IGenerator
{
public:
    virtual QList<Exercise> Generate( const QString& theLine, const Context& theContext ) const = 0;
};

#endif // IGENERATOR_H
