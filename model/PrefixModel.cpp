
#include <model/PrefixModel.h>
#include <model/Tools.h>

/**
  @brief Constructor
*/
PrefixModel::PrefixModel()
{
}

/**
  @brief Destructor
*/
PrefixModel::~PrefixModel()
{
}

/**
  @brief Add the prefixes description
  @param theLine the prefixes description
  @return if the addition is successful
*/
bool PrefixModel::Add( const QString& theLine )
{
    if( theLine.contains( ",") )
    {
        QStringList parts = theLine.split( ",", QString::SkipEmptyParts );
        bool isOK = true;
        foreach( QString p, parts )
        {
            if( !Add( p.trimmed() ) )
                isOK = false;
        }
        return isOK;
    }

    QStringList parts2 = theLine.split( "+", QString::SkipEmptyParts );
    int n = parts2.size();
    if( n==0 )
        return false;

    QString aPrefix = parts2[0].trimmed();
    QStringList& starts = myPrefixes[aPrefix];
    if( n>1 )
    {
        for( int i=1; i<n; i++ )
            starts.append( parts2[i].trimmed() );
    }
    else
        starts.append("");

    return true;
}

/**
  @brief Get the model's size
  @return the model's size
*/
uint PrefixModel::Size() const
{
    return myPrefixes.size();
}

/**
  @brief Get allowed start letters for a given prefix
  @return the allowed start letters
*/
QStringList PrefixModel::Starts( const QString& thePrefix ) const
{
    if( myPrefixes.contains(thePrefix) )
        return myPrefixes[thePrefix];
    else
        return QStringList();
}

/**
  @brief Verify if the word matches to a given prefix
  @param theWord the word to check
  @param thePrefix the prefix to check
  @return whether the word matches to the given prefix
*/
bool PrefixModel::Match( const QString& theWord, const QString& thePrefix ) const
{
    if( !myPrefixes.contains(thePrefix) )
        return false;

    QString aWordMid = theWord.trimmed().mid( thePrefix.length() );
    const QStringList& starts = myPrefixes[thePrefix];
    foreach( QString s, starts )
        if( IsEqual( s, aWordMid ) )
            return true;

    return false;
}

/**
  @brief Verify if start letters are equal to given word's part
  @param theStart the start letters to check
  @param theWordPart the word part to check
  @return if letters are equal to part
*/
bool PrefixModel::IsEqual( const QString& theStart, const QString& theWordPart ) const
{
    if( theWordPart.isEmpty() )
        return false;

    if( theStart.isEmpty() )
        return true;

    QStringList ignore = theStart.split("-", QString::SkipEmptyParts);
    QString main = ignore[0];
    QString ign = ignore.size()>1 ? ignore[1] : "";

    if( main=="<a>")
        return Tools::isVowel( theWordPart[0], ign );
    if( main=="<b>" || main=="<c>")
        return Tools::isConsonant( theWordPart[0], ign );

    return theStart == theWordPart.left( theStart.size() );
}
