
#ifndef STD_MODEL_H
#define STD_MODEL_H

#include <model/model_global.h>
#include <model/Exercise.h>
#include <model/Grammar.h>

class MODEL_API StdModel
{
public:
    StdModel();
    ~StdModel();

    bool Load( const QString& theFilePath, const QString& theLang, bool isVerbose=false );
    bool LoadPrivate( const QString& theFilePath );

    uint NbExercises() const;
    const Grammar& grammar() const;

    QString Translation( const QString& theWord ) const;

private:
    Grammar myGrammar;
    ListOfExercises myExercises;
};

#endif // STD_MODEL_H
