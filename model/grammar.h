
#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "model_global.h"
#include <QRegExp>
#include <QStringList>

class MODEL_API GrammarSet : public QStringList
{
public:
    GrammarSet( const QStringList& = QStringList() );
    GrammarSet( const QString&, int = 1 );

    QString toString() const;

    GrammarSet operator + ( const GrammarSet& ) const;
    GrammarSet operator + ( const QString& ) const;
    GrammarSet operator + ( const char* ) const;
    GrammarSet operator * ( const GrammarSet& ) const;

    GrammarSet Replaced( const QString& theStrToFind, const QString& theReplace );
};

class MODEL_API GrammarRule
{
public:
    GrammarRule( const QString& theRule );
    ~GrammarRule();

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


class MODEL_API Grammar
{
public:
    Grammar();
    ~Grammar();
};

#endif // GRAMMAR_H
