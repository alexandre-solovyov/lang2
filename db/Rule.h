
#ifndef DB_RULE_H
#define DB_RULE_H

#include <model/GrammarRule.h>
#include <QMap>

class Rules
{
public:
    Rules();
    ~Rules();

    void Add( const QString& theGroup, const QString& thePattern );
    QString Forms( const QString& theWord, const QString& theGroup, QString& theError ) const;

private:
    QMap<QString, GrammarRule> myRules;
};

#endif  // DB_READER_H
