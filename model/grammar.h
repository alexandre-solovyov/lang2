
#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <model/model_global.h>
#include <model/grammarrule.h>
#include <QMap>

class GrammarSet;
class ITense;

class MODEL_API Grammar
{
public:
    Grammar( bool isOwner=true );
    ~Grammar();

    void Add( ITense* );
    void Add( const QString& theTense, const QString& theRule );
    GrammarSet Forms( const QString& theTense, const QString& theWord ) const;

    QStringList Tenses() const;

    void CacheAllForms( const QString&, const QStringList& );
    QStringList CachedForms( const QString& = "" ) const;

    QStringList Init( const QString& ) const;

    void AddAsKnown( const QString& );
    bool IsKnown( const QString& ) const;
    uint NbKnown() const;

private:
    QMap<QString, ITense*> myTenses;
    bool myIsOwner;

    QMap<QString, QStringList> myCachedForms; //TODO: more effective forms container
    QMap<QString, QStringList> myInit;
    QMap<QString, char>        myKnown;
};

#endif // GRAMMAR_H
