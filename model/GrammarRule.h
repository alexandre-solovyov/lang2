
#ifndef GRAMMAR_RULE_H
#define GRAMMAR_RULE_H

#include <model/model_global.h>
#include <QRegExp>
#include <QStringList>

class GrammarSet;

/**
  @class GrammarRule
  @brief The implementation of the universal grammar rule
*/
class MODEL_API GrammarRule
{
public:
    GrammarRule( const QString& theRule );
    ~GrammarRule();

    bool IsSingle() const;
    bool Match( const QString& theWord ) const;
    bool Include( const GrammarRule& ) const;

    QString Group() const;
    QString Start() const;
    GrammarSet Result() const;

    GrammarSet Forms( const QString& theWord ) const;

private:
    QRegExp     myRule;      ///< the regular expression for grammar rule
    QString     myGroup;     ///< the group of the grammar rule
    QString     myStart;     ///< the start part of the grammar rule
    QStringList myResult;    ///< the result part of the grammar rule
    int         myParts;
};

#endif // GRAMMAR_RULE_H
