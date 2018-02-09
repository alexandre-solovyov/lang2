
#ifndef EG_TRANS_H
#define EG_TRANS_H

#include "igenerator.h"

class MODEL_API EG_Trans : public IGenerator
{
public:
    EG_Trans();
    virtual ~EG_Trans();

    virtual QList<Exercise> Generate( const QString& theLine, const Context& theContext ) const;
};

#endif // EG_TRANS_H
