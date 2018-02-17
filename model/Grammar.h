
#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <model/model_global.h>
#include <model/GrammarRule.h>
#include <QMap>

class GrammarSet;
class ITense;

/**
  @class Grammar
  @brief The implementation of the grammar
*/
class MODEL_API Grammar
{
public:
    Grammar( bool isOwner=true );
    ~Grammar();

    bool Add( ITense* );
    bool Add( const QString& theTense, const QString& theRule );
    GrammarSet Forms( const QString& theTense, const QString& theWord ) const;

    QStringList Tenses() const;

    void CacheAllForms( const QString&, ITense* );
    QStringList CachedForms( const QString& = "" ) const;

    QStringList Init( const QString& ) const;

    void AddAsKnown( const QString&, bool isPrivate );
    bool IsKnown( const QString& ) const;
    uint NbKnown() const;

private:
    QMap<QString, ITense*> myTenses;       ///< the map of tenses
    bool myIsOwner;                        ///< whether the grammar is owner of tenses objects

    QMap<QString, QStringList> myCachedForms;   ///< the map of cached forms
    QMap<QString, QStringList> myInit;          ///< the map of cached inverse forms
    //TODO: more effective forms container

    QMap<QString, char>        myKnown;          ///< the map of known words
    QMap<QString, char>        myKnownPrivate;   ///< the map of private known words
};

#endif // GRAMMAR_H
