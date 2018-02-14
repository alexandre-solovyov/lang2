
#ifndef IGENERATOR_H
#define IGENERATOR_H

#include <QStringList>
#include <model/exercise.h>
#include <model/model_global.h>

const QString MARK = "*";
const QString QUEST = "<?>";
const QString EQ_MARK = "=";

class MODEL_API IGenerator
{
public:
    virtual ListOfExercises Generate( const QString& theLine, const Context& theContext ) const = 0;
    virtual QString Type() const = 0;
};

#endif // IGENERATOR_H
