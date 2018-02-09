#include "model.h"
#include <QFile>

Model::Model()
{
}

Model::~Model()
{
}

bool Model::Load( const QString& theFileName )
{
    QFile aFile( theFileName );
    if( !aFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
        return false;

    QString aData = aFile.readAll();
    QStringList aLines = aData.split( "\n", QString::SkipEmptyParts );

    foreach( QString aLine, aLines )
    {
        //aLine = Simplify(aLine);
        //Add( aLine );
    }

    aFile.close();

    return true;
}
