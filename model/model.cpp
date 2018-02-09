#include "model.h"
#include <QFile>

Model::Model()
{
}

Model::~Model()
{
}

uint Model::Size() const
{
    return myLines.size();
}

bool Model::Load( const QString& theFileName )
{
    QFile aFile( theFileName );
    if( !aFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
        return false;

    QString aData = aFile.readAll();
    QStringList aLines = aData.split( "\n", QString::SkipEmptyParts );

    foreach( QString aLine, aLines )
        Add( aLine );

    aFile.close();

    return true;
}

bool Model::Add( const QString& theLine )
{
    QString aLine = theLine;
    aLine = Simplify(aLine);

    bool isOK = !aLine.isEmpty() && !HasLine( aLine );
    if( isOK )
    {
        myLines.append( aLine );
        myHashes.insert( qHash( aLine ), 0 );
    }
    return isOK;
}

bool Model::HasLine( const QString& theStr ) const
{
    uint aHash = qHash( theStr );
    return myHashes.contains( aHash );
}

QString Model::Simplify( const QString& theLine )
{
    // 1. Simplify spaces
    QString aLine = theLine.split( " ", QString::SkipEmptyParts ).join( " " );
    return aLine;
}
