
#ifndef ITENSE_H
#define ITENSE_H

#include <model/model_global.h>
#include <QString>

class GrammarSet;

class MODEL_API ITense
{
public:
    ITense( const QString& );
    virtual ~ITense();

    QString Name() const;

    virtual GrammarSet Forms( const QString& theWord ) const = 0;

private:
    QString myName;
};

#endif // ITENSE_H
