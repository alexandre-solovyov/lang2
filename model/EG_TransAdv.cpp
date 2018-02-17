
#include <model/EG_TransAdv.h>

EG_TransAdv::EG_TransAdv()
{
}

EG_TransAdv::~EG_TransAdv()
{
}

QString EG_TransAdv::Type() const
{
    return "trans_adv";
}

void EG_TransAdv::Reset()
{
}

void EG_TransAdv::Ignore( const QStringList& )
{
}

/*
void AddTr( const ListOfExercises& ex, const Context& theContext, const QString& theWord, const QString& theTrans )
{
}

void AddVTr( const ListOfExercises& ex, const Context& theContext, const QString& theWord )
{
}*/

ListOfExercises EG_TransAdv::Generate( const QString& /*theLine*/, const Context& /*theContext*/, bool& /*isOtherProduct*/ ) const
{
    ListOfExercises ex;

  /* QStringList parts = theLine.split( ":", QString::SkipEmptyParts );
    if( parts.size()==2 )
    {
        QString p1 = parts[0].trimmed();
        QString trans = parts[1].trimmed();
        QStringList parts2 = p1.split( ",", QString::SkipEmptyParts );
        if( parts2.size()==2 )
        {
            QString word = parts2[0];
            QString type = parts2[1];

            Exercise e(theContext);
            if( type=="vt" )   // verb transitive
            {
                AddTr( ex, theContext, word, trans );
                AddTr( ex, theContext, trans, word );
                AddVTr( ex, theContext, word );
            }
            else if( type=="n" )
            {
                QString w = "un " + word;
                AddTr( ex, theContext, w, trans );
                AddTr( ex, theContext, w, trans );
            }
            else if( type=="f" )
            {
                AddTr( ex, theContext, "une" + word, trans );
            }
        }
    }*/

    return ex;
}
