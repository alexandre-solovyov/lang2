
#include <model/EG_Place.h>
#include <model/Tools.h>

EG_Place::EG_Place()
{
}

EG_Place::~EG_Place()
{
}

/**
*/
QString EG_Place::Type() const
{
    return "place";
}

/**
*/
void EG_Place::Reset()
{
}

/**
*/
void EG_Place::Ignore( const QStringList& )
{
}

/**
*/
ListOfExercises EG_Place::Generate( const QString& theLine, const Context& theContext, bool& /*isOtherProduct*/ ) const
{
    ListOfExercises ex;

    int p1 = theLine.indexOf(EQ_PLACE_MARK);
    if( p1 < 0 )
        return ex;

    int p2 = theLine.indexOf(EQ_PLACE_MARK, p1+1);
    if( p2 < 0 )
        p2 = theLine.indexOf(' ', p1+1);
    if( p2 < 0 )
        p2 = theLine.size();

    QString tag = theLine.mid(p1+1, p2-p1-1);

    Exercise e1( theContext );
    e1.Tag = tag;
    e1.Question = theLine;
    e1.Question.remove(p1, p2-p1+1);
    e1.Question = Tools::simplifySpaces(e1.Question);
    e1.Answer = theLine;
    e1.Answer.remove(EQ_PLACE_MARK);
    ex.append(e1);

    return ex;
}
