
#include <model/StdModel.h>
#include <model/Tools.h>
#include <QDir>

const int     LIST_TRIM = 20;
const QString END = "_END_";

static bool     IS_VERBOSE = false;
static QString  LANG_FOLDER;
static QString  TEXTS_FOLDER;
static QString  LANG;
static StdModel MODEL;

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
		if( w==END )
			break;

        w = w.toLower();
        if( Tools::startsWithDigit(w) ||
            Tools::notLetters(w) ||
            Tools::isCyrillic(w) )
            continue;

        const Grammar& aGram = MODEL.grammar();
        QString init = aGram.Init(w).join(" ");
        /*QString init2 = aGram.Init(init).join(" ");
        Tools::print( init + " -- " + init2 );
        if(init2!=init)
            init = init2;*/

        bool known = aGram.IsKnown(init);
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
        int i = 0;
        for( ; it!=last && i<LIST_TRIM; ++it, i++ )
            Tools::print( QString( "%0: %1" ).arg(it.key()).arg(it.value()) + ";  ", false );
        if( i==LIST_TRIM )
			Tools::print( "..." );
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
    Tools::print( "There are " + QString::number(files.size()) + " texts" );

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

//#define ENGLISH
//#define FRANCAIS
#define GERMAN

int main( int /*argc*/, char** /*argv*/ )
{
#ifdef ENGLISH
    IS_VERBOSE = true;
    #ifdef WIN32
        LANG_FOLDER = "D:/asl/lang3/lang/progress/english";
        TEXTS_FOLDER = "D:/asl/lang3/lang/texts/english";
    #else
        LANG_FOLDER = QDir::home().absoluteFilePath("lang2/progress/english");
        TEXTS_FOLDER = QDir::home().absoluteFilePath("lang2/texts/english");
    #endif
    LANG = "en";
#endif

#ifdef FRANCAIS
    IS_VERBOSE = true;
    #ifdef WIN32
        LANG_FOLDER = "D:/asl/lang3/lang/progress/french";
        TEXTS_FOLDER = "D:/asl/lang3/lang/texts/french";
    #else
        LANG_FOLDER = QDir::home().absoluteFilePath("lang2/progress/french");
        TEXTS_FOLDER = QDir::home().absoluteFilePath("lang2/texts/french");
    #endif
    LANG = "fr";
#endif
#ifdef GERMAN
    IS_VERBOSE = true;
    #ifdef WIN32
        LANG_FOLDER = "D:/asl/lang3/lang/progress/german";
        TEXTS_FOLDER = "D:/asl/lang3/lang/texts/german";
    #else
        LANG_FOLDER = QDir::home().absoluteFilePath("lang2/progress/german");
        TEXTS_FOLDER = QDir::home().absoluteFilePath("lang2/texts/german");
    #endif
    LANG = "de";
#endif

    Load();

    CheckTexts( 1, false );
    //CheckTexts( 5, false );
    
    //CheckTexts( 2, true );
    //CheckTexts( 3, true );
    //CheckTexts( 4, true );
    //CheckTexts( 5, true );
    //CheckText( QDir( TEXTS_FOLDER ).absoluteFilePath("breve_histoire.txt") );


    printf("\n\n");

    return 0;
}
