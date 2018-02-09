
#ifndef MODEL_H
#define MODEL_H

#include "model_global.h"

class MODEL_API Model
{
public:
    Model();
    ~Model();

    bool Load( const QString& );
};

#endif // MODEL_H
