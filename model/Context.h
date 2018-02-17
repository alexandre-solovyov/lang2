
#ifndef CONTEXT_H
#define CONTEXT_H

#include <QString>

/**
  @struct Context
  @brief The Context structure
*/
struct Context
{
    QString Lang1;      ///< the first (input) language
    QString Lang2;      ///< the second (output, translation) language
    QString Category;   ///< the category of words/exercises
    QString Type;       ///< the type of the generator
    QString Tag;        ///< the tag (description)
};

#endif   // CONTEXT_H
