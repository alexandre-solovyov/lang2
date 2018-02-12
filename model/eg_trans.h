
#ifndef EG_TRANS_H
#define EG_TRANS_H

#include <model/igenerator.h>

class MODEL_API EG_Trans : public IGenerator
{
public:
    EG_Trans();
    virtual ~EG_Trans();

    virtual ListOfExercises Generate( const QString& theLine, const Context& theContext ) const;
    virtual QString Type() const;
};

#endif // EG_TRANS_H
