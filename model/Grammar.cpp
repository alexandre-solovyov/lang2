
#include <model/Grammar.h>
#include <model/GrammarSet.h>
#include <model/StdTense.h>
#include <model/Tools.h>

/**
  @brief Constructor
  @param isOwner whether the grammar is owner of tenses objects
*/
Grammar::Grammar( bool isOwner )
    : myIsOwner( isOwner )
{
}

/**
  @brief Destructor
*/
Grammar::~Grammar()
{
    if( myIsOwner )
    {
        QMap<QString, ITense*>::const_iterator it = myTenses.begin(), last = myTenses.end();
        for( ; it!=last; ++it )
            delete it.value();
    }
}

/**
  @brief Add a new tense
  @param theTense the new tense to add
  @return if the tense is added
*/
bool Grammar::Add( ITense* theTense )
{
    if( !theTense )
        return false;

    QString aName = theTense->Name();
    if( theTense->grammar() != this )
        theTense->setGrammar( this );
    if( myTenses.contains(aName) )
        myTenses[aName]->Unite( theTense );
    else
        myTenses[aName] = theTense;

    return true;
}

/**
  @brief Add a new rule for a tense
  @param theTense the tense where the rule should be added
  @param theRule a new rule
  @return if the rule is added
*/
bool Grammar::Add( const QString& theTense, const QString& theRule )
{
    if( !myTenses.contains(theTense) )
        Add( new StdTense( theTense, this ) );

    StdTense* aTense = dynamic_cast<StdTense*>( myTenses[theTense] );
    if( aTense )
        aTense->Add( theRule );

    return (aTense!=0);
}

/**
  @brief Build forms of a given word in the given tense
  @param theTense the tense for which the forms should be built
  @param theWord the word for which the forms should be built
  @return the set of built forms
*/
GrammarSet Grammar::Forms( const QString& theTense, const QString& theWord ) const
{
    if( myTenses.contains( theTense ) )
        return myTenses[theTense]->Forms( theWord );
    else
        return GrammarSet();
}

/**
  @brief Get list of tenses in the grammar
  @return the list of tenses
*/
QStringList Grammar::Tenses() const
{
    return myTenses.keys();
}

/**
  @brief Cache all forms of given word for the given tense
  @param theWord the word for which the forms should be cached
  @param theTense the tense for which the forms should be built and cached
*/
void Grammar::CacheAllForms( const QString& theWord, ITense* theTense )
{
    if( !theTense )
        return;

    //Tools::print( QString( "CacheAllForms: " ) + theWord );
    GrammarSet aSet = theTense->Forms( theWord );

    QStringList& lst = myCachedForms[theWord];
    foreach( QString f, aSet )
    {
        if( !lst.contains(f) )
            lst.append(f);
        if( !myInit[f].contains( theWord ) )
            myInit[f].append( theWord );
        //Tools::print( "  " + f );
    }
}

/**
  @brief Get all cached forms of the given word for the given tense
  @param theWord the word for which the cached forms should be returned
  @return the list of cached forms
*/
QStringList Grammar::CachedForms( const QString& theWord ) const
{
    if( theWord.isEmpty() )
        return myCachedForms.keys();
    else if( myCachedForms.contains( theWord ) )
        return myCachedForms[theWord];
    else
        return QStringList();
}

/**
  @brief Get cached initial form of the word
    (usually one form, but in rare cases several initial forms are possible)
  @param theWord the word for which the initial form should be returned
  @return cached initial form (if any) or the same form (if the initial form is not found).
*/
QStringList Grammar::Init( const QString& theWord ) const
{
    if( myInit.contains( theWord ) )
        return myInit[theWord];
    else
        return QStringList() << theWord;
}

/**
  @brief Cache the given word as "known"
  @param theWord the word to cache
  @param isPrivate if the "private" list should be used
*/
void Grammar::AddAsKnown( const QString& theWord, bool isPrivate )
{
    QString aWord = theWord.toLower().trimmed();
    ( isPrivate ? myKnownPrivate : myKnown )[aWord] = ' ';
}

/**
  @brief Check if the given word is "known"
  @param theWord the word to check
  @return if the given word is "known"
*/
bool Grammar::IsKnown( const QString& theWord ) const
{
    QString aWord = theWord.toLower().trimmed();
    return myKnown.contains( aWord ) || myKnownPrivate.contains( aWord );
}

/**
  @brief Calculate the number of "known" words (without the private list)
  @return the number of known words
*/
uint Grammar::NbKnown() const
{
    return myKnown.size();
}

bool Grammar::AddPrefix( const QString& theLine )
{
    return myPrefixModel.Add( theLine );
}

const PrefixModel* Grammar::prefixModel() const
{
    return &myPrefixModel;
}
