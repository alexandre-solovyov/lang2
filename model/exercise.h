
#ifndef EXERCISE_H
#define EXERCISE_H

#include <model/model_global.h>
#include <model/context.h>
#include <QList>

struct Exercise : public Context
{
    Exercise()
    {
    }
    Exercise( const Context& c )
    {
        Lang1 = c.Lang1;
        Lang2 = c.Lang2;
        Category = c.Category;
        Type = c.Type;
        Tag = c.Tag;
    }

    QString Question;
    QString Answer;

    bool operator == ( const Exercise& ) const;
};

class MODEL_API ListOfExercises : public QList<Exercise>
{
public:
    ListOfExercises();
    ~ListOfExercises();

    ListOfExercises Filter( const QString& theType,
                            const QString& theLang1,
                            const QString& theLang2 ) const;

    ListOfExercises Random( int theNbItems ) const;

    QStringList Shuffle( const Exercise&, const ListOfExercises&, int theNbShuffle=20 ) const;
};

#endif  // EXERCISE_H
