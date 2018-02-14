
#ifndef EG_TRANS_H
#define EG_TRANS_H

#include <model/igenerator.h>

class MODEL_API EG_Trans : public IGenerator
{
public:
    EG_Trans( bool isBoth=true, bool isSimple=false );
    virtual ~EG_Trans();

    virtual ListOfExercises Generate( const QString& theLine, const Context& theContext, bool& isOtherProduct ) const;
    virtual QString Type() const;

private:
    bool myIsBoth;
    bool myIsSimple;
};

#endif // EG_TRANS_H
