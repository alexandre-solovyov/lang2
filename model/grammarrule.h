
#ifndef GRAMMAR_RULE_H
#define GRAMMAR_RULE_H

#include <model/model_global.h>
#include <QRegExp>
#include <QStringList>

class GrammarSet;

class MODEL_API GrammarRule
{
public:
    GrammarRule( const QString& theRule );
    ~GrammarRule();

    bool IsSingle() const;
    bool Match( const QString& theWord ) const;
    QString Group() const;
    QString Start() const;
    GrammarSet Result() const;

    GrammarSet Forms( const QString& theWord ) const;

private:
    QRegExp myRule;
    QString myGroup;
    QString myStart;
    QStringList myResult;
};

#endif // GRAMMAR_RULE_H
