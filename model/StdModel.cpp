
#include <model/StdModel.h>
#include <model/LangFile.h>
#include <model/EG_One.h>
#include <model/EG_Trans.h>
#include <model/EG_Forms.h>
#include <model/EG_Place.h>
#include <model/Tools.h>
#include <QFile>
#include <QDebug>

StdModel::StdModel()
{
}

StdModel::~StdModel()
{
}

uint StdModel::NbExercises() const
{
    return (uint)myExercises.size();
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
        gen.append( new EG_Forms(&myGrammar, false) );
        gen.append( new EG_Place() );
        if( isVerbose )
            Tools::print( "" );

        myExercises = lf.Build( gen, isVerbose );

        foreach( const Exercise& e, myExercises )
        {
            QString phrase;
            if( e.Lang2==theLang )
                phrase = e.Answer;
            //else if( e.Lang1==theLang )
            //    phrase = e.Question;

            QStringList words = phrase.split(QRegExp("\\W+"), QString::SkipEmptyParts );
            foreach( QString w, words )
                myGrammar.AddAsKnown( w, false );
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

    return true;
}

QStringList StdModel::Translation( const QString& theWord ) const
{
    QStringList aResult;
    QString aLeft = theWord + " = ";
    foreach( const Exercise& e, myExercises )
    {
        if(e.Question.toLower().contains(aLeft))
        {
            //qDebug() << e.Question << e.Answer;
            aResult.append(e.Answer);
        }
    }
    return aResult;
}
