
#include <model/PrefixModel.h>
#include <model/Tools.h>

PrefixModel::PrefixModel()
{
}

PrefixModel::~PrefixModel()
{
}

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

uint PrefixModel::Size() const
{
    return myPrefixes.size();
}

QStringList PrefixModel::Starts( const QString& thePrefix ) const
{
    if( myPrefixes.contains(thePrefix) )
        return myPrefixes[thePrefix];
    else
        return QStringList();
}

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
