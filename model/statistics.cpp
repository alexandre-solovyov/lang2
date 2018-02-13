
#include <model/statistics.h>

Statistics::Statistics()
{
}

Statistics::~Statistics()
{
}

void Statistics::Add( const QString& theStr, bool isCorrect )
{
    int k = key( theStr );
    if( !myData.contains( k ) )
    {
        Data d;
        d.correct = 0;
        d.incorrect = 0;
        myData[k] = d;
    }
    if( isCorrect )
        myData[key(theStr)].correct++;
    else
        myData[key(theStr)].incorrect++;
}

int Statistics::NbCorrect( const QString& theStr ) const
{
    int k = key( theStr );
    if( myData.contains( k ) )
        return myData[k].correct;
    else
        return 0;
}

int Statistics::NbIncorrect( const QString& theStr ) const
{
    int k = key( theStr );
    if( myData.contains( k ) )
        return myData[k].incorrect;
    else
        return 0;
}

double Statistics::Weight( const QString& ) const
{
    //TODO
    return 0;
}

int Statistics::key( const QString& theStr ) const
{
    return qHash( theStr );
}
