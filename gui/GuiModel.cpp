
#include <gui/GuiModel.h>
#include <model/eg_one.h>
#include <model/eg_trans.h>

GuiModel::GuiModel()
    : myIndex( -1 )
{
}

GuiModel::~GuiModel()
{
}

void GuiModel::Load( const QString& thePath )
{
    // TODO: load a directory
    Model::Load( thePath );

    QList<IGenerator*> gen;
    gen.append( new EG_One() );
    gen.append( new EG_Trans() );
    myExercises = Build(gen);
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
