
#include <model/Exercise.h>
#include <QStringList>

Exercise::Exercise()
{
}

Exercise::Exercise( const Context& theContext )
{
    Lang1 = theContext.Lang1;
    Lang2 = theContext.Lang2;
    Category = theContext.Category;
    Type = theContext.Type;
    Tag = theContext.Tag;
}

bool Exercise::operator == ( const Exercise& e ) const
{
    return Lang1==e.Lang1 &&
           Lang2==e.Lang2 &&
           Category==e.Category &&
           Type==e.Type &&
           Question==e.Question &&
           Answer==e.Answer &&
           Tag==e.Tag;
}

ListOfExercises::ListOfExercises()
{
}

ListOfExercises::~ListOfExercises()
{
}

ListOfExercises ListOfExercises::Filter( const QString& theType,
                                         const QString& theLang1,
                                         const QString& theLang2 ) const
{
    ListOfExercises res;

    ListOfExercises::const_iterator it = begin(), last = end();
    for( ; it!=last; ++it)
    {
        if( ( theType.isEmpty() || it->Type==theType ) &&
            ( theLang1.isEmpty() || it->Lang1==theLang1 ) &&
            ( theLang2.isEmpty() || it->Lang2==theLang2 ) )
        {
            res.append( *it );
        }
    }

    return res;
}

ListOfExercises ListOfExercises::Random( int theNbItems ) const
{
    if( empty() )
        return ListOfExercises();

    QList<int> indices;
    for( int i=0; i<theNbItems; i++ )
    {
        int q = qrand()%size();
        if (!indices.contains(q))
            indices.append(q);
    }

    ListOfExercises res;
    foreach( int i, indices )
        res.append( operator[](i));

    return res;
}

QStringList ListOfExercises::Shuffle( const Exercise& theExercise, const ListOfExercises& theVariants, int theNbShuffle ) const
{
    QStringList res;
    res.append( theExercise.Answer );
    foreach( Exercise e, theVariants )
        if( !res.contains(e.Answer) )
            res.append( e.Answer );

    for( int i=0; i<theNbShuffle; i++ )
    {
        int p = rand()%res.size();
        int q = rand()%res.size();
        qSwap( res[p], res[q] );
    }

    return res;
}
