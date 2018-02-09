
#ifndef EXERCISE_H
#define EXERCISE_H

#include <model/context.h>

struct Exercise : public Context
{
    Exercise( const Context& c )
    {
        Lang1 = c.Lang1;
        Lang2 = c.Lang2;
        Category = c.Category;
    }

    uint EType;
    QString Question;
    QString Answer;
    QString Tag;
};

#endif  // EXERCISE_H
