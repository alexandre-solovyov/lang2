
#ifndef IGENERATOR_H
#define IGENERATOR_H

#include <QStringList>
#include <model/Exercise.h>
#include <model/model_global.h>

const QString MARK = "*";
const QString QUEST = "<?>";
const QString EQ_MARK = "=";
const QString EQ_PLACE_MARK = "@";

/**
  @class IGenerator
  @brief The interface for exercise generator
*/
class MODEL_API IGenerator
{
public:
    /**
      @brief Reset the generator's internal state
    */
    virtual void Reset() = 0;

    /**
      @brief Set ignore list for the generator
      @param theIgnoreList the ignore list
    */
    virtual void Ignore( const QStringList& theIgnoreList ) = 0;

    /**
      @brief Generate the exercise(s) from a given line
      @param theLine the input line
      @param theContext the current context
      @param isOtherProduct whether the generator produces other output (not only exercises)
      @return list of generated exercises
    */
    virtual ListOfExercises Generate( const QString& theLine, const Context& theContext, bool& isOtherProduct ) const = 0;

    /**
      @brief Get the type of generator
      @return the type of generator
    */
    virtual QString Type() const = 0;
};

#endif // IGENERATOR_H
