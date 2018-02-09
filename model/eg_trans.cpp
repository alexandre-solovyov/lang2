
#include <model/eg_trans.h>

EG_Trans::EG_Trans()
{
}

EG_Trans::~EG_Trans()
{
}

QList<Exercise> EG_Trans::Generate( const QString& theLine, const Context& theContext ) const
{
    const QString EQ_MARK = "=";

    QList<Exercise> ex;

    QStringList parts = theLine.split( EQ_MARK, QString::SkipEmptyParts );
    if( parts.size()==2 )
    {
        QString p1 = parts[0].trimmed();
        QString p2 = parts[1].trimmed();

        p1.replace( MARK, "" );
        p2.replace( MARK, "" );

        Exercise e1( theContext );
        e1.Question = QString( "%0 %1 %2").arg( p1 ).arg( EQ_MARK ).arg( QUEST );
        e1.Answer = p2;
        ex.append(e1);

        Exercise e2( theContext );
        qSwap( e2.Lang1, e2.Lang2 );
        e2.Question = QString( "%0 %1 %2").arg( p2 ).arg( EQ_MARK ).arg( QUEST );
        e2.Answer = p1;
        ex.append(e2);
    }

    return ex;
}
