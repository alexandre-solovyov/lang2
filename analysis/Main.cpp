
#include <model/StdModel.h>
#include <model/Tools.h>

int main( int argc, char** argv )
{
    StdModel model;
    model.Load( "D:/asl/lang3/lang/progress/french", "fr", false );

    Tools::print( QString("Nb exercises: %0").arg( model.NbExercises() ) );
    Tools::print( QString("Nb known: %0").arg( model.grammar().NbKnown() ) );

    QString aFileName = "D:/asl/lang3/lang/texts/french/t0001_paris.txt";
    QFile aFile( aFileName );
    if( !aFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        Tools::print( "File cannot be opened" );
        return 0;
    }

    QString aData = aFile.readAll();
    QStringList words = aData.split( QRegExp("\\W+"), QString::SkipEmptyParts );

    QMap<QString, int> unknown;
    foreach( QString w, words )
    {
        w = w.toLower();
        if( Tools::startsWithDigit(w) )
            continue;
        QString init = model.grammar().Init(w).join(" ");
        bool known = model.grammar().IsKnown(init);
        //Tools::print( QString( "%0 -- %1 -- %2" ).arg( w ).arg( init ).arg( known ) );
        if( !known )
        {
            if( unknown.contains(init) )
                unknown[init]++;
            else
                unknown[init] = 1;
        }
    }

    Tools::print( "" );
    Tools::print( QString("Nb unknown: %0").arg(unknown.size()) );

    QMap<QString, int>::const_iterator it = unknown.begin(), last = unknown.end();
    for( ; it!=last; it++ )
        Tools::print( QString( "%0: %1" ).arg(it.key()).arg(it.value()) );

    return 0;
}
