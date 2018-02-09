#include <model/model.h>
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

QList<Exercise> Model::Build( const QList<IGenerator*>& theGenerators )
{
    QList<Exercise> exercises;
    Context aContext;

    foreach( QString aLine, myLines )
    {
        if( aLine.startsWith("//!") )
        {
            // Special comment
            QStringList aParts = aLine.mid( 3 ).split( ":", QString::KeepEmptyParts );
            if( aParts.size()==2 )
            {
                ChangeContext( aContext, aParts[0].trimmed(), aParts[1].trimmed() );
            }
        }
        else if( aLine.startsWith("//") || aLine.startsWith("#"))
        {
            // Ordinary comment
            continue;
        }
        else
        {
            foreach( IGenerator* aGenerator, theGenerators )
            {
                QList<Exercise> aLocal = aGenerator->Generate( aLine, aContext );
                foreach( Exercise e, aLocal )
                    exercises.append( e );
            }
        }
    }

    return exercises;
}

void Model::ChangeContext( Context& theContext, const QString& theKey, const QString& theValue )
{
    if( theKey=="lang" )
    {
        QStringList aParts = theValue.split( ",", QString::KeepEmptyParts );
        if( aParts.size()==2 )
        {
            theContext.Lang1 = aParts[0].trimmed();
            theContext.Lang2 = aParts[1].trimmed();
        }
    }
    else if( theKey=="date")
    {
        //TODO
    }
    else if( theKey=="category")
    {
        theContext.Category = theValue;
    }
}
