
#include <model/EG_Trans.h>

EG_Trans::EG_Trans( bool isBoth, bool isSimple )
    : myIsBoth( isBoth ), myIsSimple( isSimple )
{
}

EG_Trans::~EG_Trans()
{
}

/**
*/
QString EG_Trans::Type() const
{
    return "trans";
}

/**
*/
void EG_Trans::Reset()
{
}

/**
*/
void EG_Trans::Ignore( const QStringList& )
{
}

/**
*/
ListOfExercises EG_Trans::Generate( const QString& theLine, const Context& theContext, bool& isOtherProduct ) const
{
    isOtherProduct = false;
    ListOfExercises ex;

    QStringList parts = theLine.split( EQ_MARK, QString::SkipEmptyParts );
    if( parts.size()==2 )
    {
        QString p1 = parts[0].trimmed();
        QString p2 = parts[1].trimmed();

        p1.replace( MARK, "" );
        p2.replace( MARK, "" );

        Exercise e1( theContext );
        if( myIsSimple )
            e1.Question = p1;
        else
            e1.Question = QString( "%0 %1 %2").arg( p1 ).arg( EQ_MARK ).arg( QUEST );
        e1.Answer = p2;
        ex.append(e1);

        if( myIsBoth )
        {
            Exercise e2( theContext );
            qSwap( e2.Lang1, e2.Lang2 );
            if( myIsSimple )
                e2.Question = p2;
            else
                e2.Question = QString( "%0 %1 %2").arg( p2 ).arg( EQ_MARK ).arg( QUEST );
            e2.Answer = p1;
            ex.append(e2);
        }
    }

    return ex;
}
