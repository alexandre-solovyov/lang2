
#include <gui/GuiModel.h>
#include <model/eg_one.h>
#include <model/eg_trans.h>

GuiModel::GuiModel()
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
}

QStringList GuiModel::randomExercise()
{
    int n = myExercises.size();
    if( n==0 )
        return QStringList();

    int anIndex = qrand()%n;
    Exercise e = myExercises[anIndex];
    QString q = e.Question;

    QStringList parts = q.split( QUEST, QString::KeepEmptyParts );
    for( int i=0, m=parts.size(); i<m; i++ )
            parts[i] = parts[i].trimmed();

    while( parts.size() < 2 )
        parts.append("");

    return parts;
}
