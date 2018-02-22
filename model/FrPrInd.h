
#ifndef FR_PR_IND_H
#define FR_PR_IND_H

#include <model/ITense.h>

class MODEL_API FrPrInd : public ITense
{
public:
    FrPrInd( Grammar* );
    virtual ~FrPrInd();

    virtual GrammarSet Forms( const QString& theWord ) const;
};

#endif // FR_PR_IND_H
