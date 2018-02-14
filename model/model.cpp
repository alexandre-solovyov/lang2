
#include <model/model.h>
#include <model/tools.h>
#include <QFile>
#include <QDir>
#include <QTime>

Model::Model()
{
}

Model::~Model()
{
}

uint Model::Size() const
{
    int s = 0;
    foreach( const FileData& f, myFiles )
        s += f.Lines.size();
    return s;
}

bool Model::Load( const QString& theFilePath, bool isVerbose )
{
    static QStringList MASK = QStringList() << "*.lang";
    if( QFileInfo( theFilePath ).isDir() )
    {
        QDir aDir( theFilePath );
        QFileInfoList files = aDir.entryInfoList( MASK );
        bool isOK = true;
        foreach( QFileInfo info, files )
            if( !Load( info.absoluteFilePath(), isVerbose ) )
                isOK = false;
        return isOK;
    }

    if( isVerbose )
        Tools::print( "Loading file: " + theFilePath );

    QFile aFile( theFilePath );
    if( !aFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        if( isVerbose )
            Tools::print( "File cannot be opened" );
        return false;
    }

    QString aData = aFile.readAll();
    QStringList aLines = aData.split( "\n", QString::SkipEmptyParts );

    int index = AddFile( theFilePath );
    foreach( QString aLine, aLines )
        Add( index, aLine );

    aFile.close();

    return true;
}

int Model::AddFile( const QString& theFilePath )
{
    FileData d;
    d.Name = theFilePath;
    myFiles.append( d );
    return myFiles.size()-1;
}

bool Model::Add( int theFileIndex, const QString& theLine )
{
    QString aLine = theLine;
    aLine = Simplify(aLine);

    bool isOK = !aLine.isEmpty() && !HasLine( aLine );
    if( isOK )
    {
        myFiles[theFileIndex].Lines.append( aLine );
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
    QString aLine = theLine.split( " ", QString::SkipEmptyParts ).join( " " );
    return aLine;
}

ListOfExercises Model::Build( const QList<IGenerator*>& theGenerators, bool isVerbose )
{
    ListOfExercises exercises;
    Context aContext;

    QTime t;
    t.start();

    foreach( const FileData& file, myFiles )
    {
        if( isVerbose )
            Tools::print( QString( "Building file: %0..." ).arg( file.Name ) );

        foreach( QString aLine, file.Lines )
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
                int aNbEx = 0;
                int aNbOther = 0;
                foreach( IGenerator* aGenerator, theGenerators )
                {
                    aContext.Type = aGenerator->Type();
                    QString aTag = ExtractTag( aLine );
                    aContext.Tag = aTag;

                    bool isOtherProduct;
                    ListOfExercises aLocal = aGenerator->Generate( aLine, aContext, isOtherProduct );

                    aNbEx += aLocal.size();
                    if( isOtherProduct )
                        aNbOther++;

                    foreach( Exercise e, aLocal )
                        exercises.append( e );
                }

                if( aNbEx==0 && aNbOther==0 && isVerbose )
                {
                    Tools::print( QString( "  WARNING: the line '%0' produced no exercises" ).arg( aLine ) );
                }
            }
        }
    }

    double build_time = t.elapsed() * 0.001;
    if( isVerbose )
         Tools::print( QString( "Build time: %0 sec" ).arg( build_time, 0, 'f', 3 ) );

    return exercises;
}

void Model::ChangeContext( Context& theContext, const QString& theKey, const QString& theValue ) const
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

QString Model::ExtractTag( QString& theLine ) const
{
    static QRegExp TAG_PATTERN("^\\s*\\[(\\w+)\\]");

    int anIndex = theLine.indexOf(TAG_PATTERN);
    if( anIndex < 0 )
        return "";

    QString aTag = TAG_PATTERN.cap( 1 );
    theLine.remove( 0, anIndex+TAG_PATTERN.matchedLength() );
    theLine = theLine.trimmed();
    return aTag;
}
