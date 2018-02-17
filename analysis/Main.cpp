
#include <model/StdModel.h>
#include <model/Tools.h>
#include <QDir>

#ifdef WIN32
    const QString LANG_FOLDER = "D:/asl/lang3/lang/progress/french";
    const QString TEXTS_FOLDER = "D:/asl/lang3/lang/texts/french";
#else
    const QString LANG_FOLDER = QDir::home().absoluteFilePath("lang2/progress/french");
    const QString TEXTS_FOLDER = QDir::home().absoluteFilePath("lang2/texts/french");
#endif

const QString LANG = "fr";

bool IS_VERBOSE = false;
const int  LIST_TRIM = 70;

StdModel MODEL;

void Load()
{
    MODEL.Load( LANG_FOLDER, LANG, IS_VERBOSE );
    MODEL.LoadPrivate( LANG_FOLDER + "/private" );

    if( IS_VERBOSE )
    {
        Tools::print( "" );

        Tools::print( QString("Nb exercises: %0").arg( MODEL.NbExercises() ) );
    }

    // This information should be always printed
    Tools::print( QString("Nb known: %0").arg( MODEL.grammar().NbKnown() ) );
    Tools::print( "" );
}

bool CheckText( const QString& thePath )
{
    QFile aFile( thePath );
    Tools::print( QString( "Text file: %0").arg( thePath ) );
    if( !aFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        Tools::print( "File cannot be opened" );
        return false;
    }

    QString aData = aFile.readAll();
    QStringList words = aData.split( QRegExp("\\W+"), QString::SkipEmptyParts );

    QMap<QString, int> unknown;
    foreach( QString w, words )
    {
        w = w.toLower();
        if( Tools::startsWithDigit(w) )
            continue;
        QString init = MODEL.grammar().Init(w).join(" ");
        bool known = MODEL.grammar().IsKnown(init);
        //Tools::print( QString( "%0 -- %1 -- %2" ).arg( w ).arg( init ).arg( known ) );
        if( !known )
        {
            if( unknown.contains(init) )
                unknown[init]++;
            else
                unknown[init] = 1;
        }
    }

    if( IS_VERBOSE )
        Tools::print( "" );

    Tools::print( QString("Nb unknown: %0").arg(unknown.size()) );

    if( IS_VERBOSE )
    {
        QMap<QString, int>::const_iterator it = unknown.begin(), last = unknown.end();
        for( ; it!=last; it++ )
            Tools::print( QString( "%0: %1" ).arg(it.key()).arg(it.value()) );
    }
    else
    {
        QString words = QStringList(unknown.keys()).join( ", " );
        words = words.left( LIST_TRIM );
        Tools::print( "  " + words );
    }
    return true;
}

void CheckTexts( int theIndex, bool isSeveral )
{
    static QStringList TEXT_MASK = QStringList() << "*.txt";
    QDir aDir( TEXTS_FOLDER );
    QFileInfoList files = aDir.entryInfoList( TEXT_MASK );

    if( isSeveral )
    {
        int n = qMin( files.size(), theIndex );
        if( theIndex==0 )
            n = files.size();

        for( int i=0; i<n; i++ )
            CheckText( files[i].absoluteFilePath() );
    }
    else
        CheckText( files[theIndex-1].absoluteFilePath() );
}

int main( int /*argc*/, char** /*argv*/ )
{
    IS_VERBOSE = false;
    Load();

    CheckTexts( 3, true );
    //CheckTexts( 4, false );

    return 0;
}
