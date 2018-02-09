
#include <model/eg_one.h>
#include <QRegExp>

EG_One::EG_One()
{
}

EG_One::~EG_One()
{
}

QList<Exercise> EG_One::Generate( const QString& theLine, const Context& theContext ) const
{
    static QRegExp PATTERN( QString( "\\%0[\\w\\-]+" ).arg( MARK ) );

    QList<Exercise> ex;

    int anOffset = 0;

    Exercise e( theContext );
    while( true )
    {
        int anIndex = PATTERN.indexIn( theLine, anOffset );
        if( anIndex>=0 )
        {
            QString word = PATTERN.cap();
            //printf( "%s\n", word.toStdString().c_str() );
            anOffset = anIndex + 1;

            QString aQuest = theLine;
            aQuest.replace( anIndex, word.size(), QUEST );
            aQuest.replace( MARK, "" );

            e.Question = aQuest;
            e.Answer = word.mid( 1 );
            e.Tag = ""; //TODO: tag

            ex.append( e );
        }
        else
            break;
    }

    return ex;
}
