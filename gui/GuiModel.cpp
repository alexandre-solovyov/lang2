
#include <gui/GuiModel.h>
#include <model/EG_One.h>
#include <model/EG_Trans.h>
#include <model/EG_Forms.h>
#include <model/Tools.h>
#include <QFile>

GuiModel::GuiModel()
    : myIndex( -1 )
{
}

GuiModel::~GuiModel()
{
}

void GuiModel::Load( const QString& thePath )
{
    bool isVerbose = true;

    LangFile::Load( thePath, isVerbose );

    QList<IGenerator*> gen;
    gen.append( new EG_One() );
    gen.append( new EG_Trans() );
    gen.append( new EG_Forms(&myGrammar, false) );

    myExercises = Build( gen, isVerbose );
    myIndex = -1;
}

QStringList GuiModel::randomExercise()
{
    int n = myExercises.size();
    if( n==0 )
        return QStringList();

    myIndex = qrand()%n;
    Exercise e = myExercises[myIndex];
    QString q = e.Question;

    QStringList parts = q.split( QUEST, QString::KeepEmptyParts );
    while( parts.size() < 2 )
        parts.append("");

    return parts;
}

QString GuiModel::normalize( const QString& theAnswer )
{
    return Tools::normalize( theAnswer );
}

bool GuiModel::checkAnswer( const QString& theAnswer )
{
    if( myIndex < 0 )
        return false;

    //TODO: more intelligent check
    return myExercises[myIndex].Answer.toLower()==theAnswer.toLower();
}

QString GuiModel::answer() const
{
    if( myIndex < 0 )
        return "";
    else
        return myExercises[myIndex].Answer;
}

QString GuiModel::readFile( const QString& theFilePath )
{
    Tools::print(theFilePath);
    QFile aFile( theFilePath );
    if( !aFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
        return "";

    QString aData = aFile.readAll();
    aFile.close();
    return aData;
}
