
#ifndef GRAMMAR_SET_H
#define GRAMMAR_SET_H

#include <model/model_global.h>
#include <QStringList>

class MODEL_API GrammarSet : public QStringList
{
public:
    GrammarSet( const QStringList& = QStringList() );
    GrammarSet( const QString&, int = 1 );
    GrammarSet( const QString&, const QString& );

    QString toString() const;

    GrammarSet operator + ( const GrammarSet& ) const;
    GrammarSet operator + ( const QString& ) const;
    GrammarSet operator + ( const char* ) const;
    GrammarSet operator * ( const GrammarSet& ) const;

    GrammarSet Replaced( const QString& theStrToFind, const QString& theReplace );

protected:
    QString sum( const QString& theArg1, const QString& theArg2 ) const;
};

GrammarSet operator + ( const QString&, const GrammarSet& );

#endif // GRAMMAR_SET_H
