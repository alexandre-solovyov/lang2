
#include <model/grammar.h>
#include <model/grammarset.h>
#include <model/stdtense.h>
#include <model/tools.h>

Grammar::Grammar( bool isOwner )
    : myIsOwner( isOwner )
{
}

Grammar::~Grammar()
{
    if( myIsOwner )
    {
        QMap<QString, ITense*>::const_iterator it = myTenses.begin(), last = myTenses.end();
        for( ; it!=last; it++ )
            delete it.value();
    }
}

void Grammar::Add( ITense* theTense )
{
    if( theTense )
        myTenses[theTense->Name()] = theTense;
}

void Grammar::Add( const QString& theTense, const QString& theRule )
{
    if( !myTenses.contains(theTense) )
        Add( new StdTense( theTense, this ) );

    StdTense* st = dynamic_cast<StdTense*>( myTenses[theTense] );
    if( st )
    {
        st->Add( theRule );
        //Tools::print( theRule );
    }
}

GrammarSet Grammar::Forms( const QString& theTense, const QString& theWord ) const
{
    if( myTenses.contains( theTense ) )
        return myTenses[theTense]->Forms( theWord );
    else
        return GrammarSet();
}

QStringList Grammar::Tenses() const
{
    return myTenses.keys();
}

void Grammar::CacheAllForms( const QString& theWord, const QStringList& theTenses )
{
    foreach( QString aTense, theTenses )
    {
        //Tools::print( QString( "CacheAllForms: " ) + theWord );
        GrammarSet aSet = myTenses[aTense]->Forms( theWord );

        QStringList& lst = myCachedForms[theWord];
        foreach( QString f, aSet )
        {
            lst.append(f);
            if( !myInit[f].contains( theWord ) )
                myInit[f].append( theWord );
            //Tools::print( "  " + f );
        }
    }
}

QStringList Grammar::CachedForms( const QString& theWord ) const
{
    if( theWord.isEmpty() )
        return myCachedForms.keys();
    else if( myCachedForms.contains( theWord ) )
        return myCachedForms[theWord];
    else
        return QStringList();
}

QStringList Grammar::Init( const QString& theWord ) const
{
    if( myInit.contains( theWord ) )
        return myInit[theWord];
    else
        return QStringList() << theWord;

}

void Grammar::AddAsKnown( const QString& theWord )
{
    myKnown[theWord] = ' ';
}

bool Grammar::IsKnown( const QString& theWord ) const
{
    return myKnown.contains( theWord );
}

uint Grammar::NbKnown() const
{
    return myKnown.size();
}
