
#include <model/LangFile.h>
#include <model/tools.h>
#include <QFile>
#include <QDir>
#include <QTime>

LangFile::LangFile()
{
}

LangFile::~LangFile()
{
}

uint LangFile::NbLines() const
{
    uint s = 0;
    foreach( const FileData& f, myFiles )
        s += f.Lines.size();
    return s;
}

bool LangFile::Load( const QString& theFilePath, bool isVerbose )
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

uint LangFile::AddFile( const QString& theFilePath )
{
    FileData d;
    d.Name = theFilePath;
    myFiles.append( d );
    myHashes.append( QHash<uint, uint>() );
    return myFiles.size()-1;
}

bool LangFile::Add( uint theFileIndex, const QString& theLine )
{
    QString aLine = theLine;
    aLine = Simplify(aLine);

    bool isOK = !aLine.isEmpty() && !HasLine( theFileIndex, aLine );
    if( isOK )
    {
        myFiles[theFileIndex].Lines.append( aLine );
        myHashes[theFileIndex].insert( qHash( aLine ), 0 );
    }
    return isOK;
}

bool LangFile::HasLine( uint theFileIndex, const QString& theStr ) const
{
    uint aHash = qHash( theStr );
    return myHashes[theFileIndex].contains( aHash );
}

QString LangFile::Simplify( const QString& theLine )
{
    QString aLine = theLine.split( " ", QString::SkipEmptyParts ).join( " " );

    int anIndex = aLine.indexOf("//");
    if( anIndex>=0 && aLine.mid(anIndex, 3)!="//!" )
        aLine = aLine.left( anIndex ).trimmed();

    anIndex  = aLine.indexOf("#");
    if( anIndex>=0 )
        aLine = aLine.left( anIndex ).trimmed();

    return aLine;
}

ListOfExercises LangFile::Build( const QList<IGenerator*>& theGenerators, bool isVerbose )
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
                    ChangeContext( aContext, aParts[0].trimmed(), aParts[1].trimmed(), theGenerators );
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

                QString aTag = ExtractTag( aLine );
                aContext.Tag = aTag;

                foreach( IGenerator* aGenerator, theGenerators )
                {
                    aContext.Type = aGenerator->Type();

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

        foreach( IGenerator* aGenerator, theGenerators )
            aGenerator->Reset();
    }

    double build_time = t.elapsed() * 0.001;
    if( isVerbose )
         Tools::print( QString( "Build time: %0 sec" ).arg( build_time, 0, 'f', 3 ) );

    return exercises;
}

void LangFile::ChangeContext( Context& theContext,
                              const QString& theKey,
                              const QString& theValue,
                              const QList<IGenerator*>& theGenerators ) const
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
    else if( theKey=="category" )
    {
        theContext.Category = theValue;
    }
    else if( theKey=="ignore" )
    {
        foreach( IGenerator* aGenerator, theGenerators )
            aGenerator->Ignore( theValue.split( ", ", QString::SkipEmptyParts ) );
    }
}

QString LangFile::ExtractTag( QString& theLine ) const
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
