
#include <model/StdModel.h>
#include <model/LangFile.h>
#include <model/EG_One.h>
#include <model/EG_Trans.h>
#include <model/EG_Forms.h>
#include <model/Tools.h>
#include <QFile>

StdModel::StdModel()
{
}

StdModel::~StdModel()
{
}

uint StdModel::NbExercises() const
{
    return myExercises.size();
}

const Grammar& StdModel::grammar() const
{
    return myGrammar;
}

bool StdModel::Load( const QString& theFilePath, const QString& theLang, bool isVerbose )
{
    LangFile lf;
    bool isOK = lf.Load( theFilePath, isVerbose );

    if( isOK )
    {
        QList<IGenerator*> gen;
        gen.append( new EG_One() );
        gen.append( new EG_Trans() );
        gen.append( new EG_Forms(&myGrammar) );
        myExercises = lf.Build(gen);

        foreach( const Exercise& e, myExercises )
        {
            if( e.Lang2==theLang )
            {
                QStringList words = e.Answer.split(QRegExp("\\W+"), QString::SkipEmptyParts );
                foreach( QString w, words )
                {
                    myGrammar.AddAsKnown( w, false );
                }
            }
        }

        //Tools::print( "" );
    }

    return isOK;
}

bool StdModel::LoadPrivate( const QString& theFilePath )
{
    QFile aFile( theFilePath );
    if( !aFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
        return false;

    QString aData = aFile.readAll();
    QStringList aLines = aData.split( "\n", QString::SkipEmptyParts );

    foreach( QString aLine, aLines )
        myGrammar.AddAsKnown( aLine, true );
}
