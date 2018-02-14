
#include <model/eg_forms.h>
#include <model/tools.h>
#include <model/grammar.h>

const QString FORMS_MARK = ">>";

EG_Forms::EG_Forms( Grammar* theGrammar )
    : EG_Trans(false, true), myGrammar( theGrammar )
{
}

EG_Forms::~EG_Forms()
{
}

QString EG_Forms::Type() const
{
    return "forms";
}

ListOfExercises EG_Forms::Generate( const QString& theLine, const Context& theContext ) const
{
    ListOfExercises ex;

    if( theLine.contains( FORMS_MARK ) )
    {
        if( myGrammar )
            myGrammar->Add( theContext.Tag, theLine );

        return ex;
    }

    if( theLine.contains( EQ_MARK ) )
    {
        ListOfExercises ex2 = EG_Trans::Generate( theLine, theContext );
        if( ex2.length() == 1 )
        {
            //Tools::print( ex2[0].Question );
            //TODO: support multi-word forms (?)
            myGrammar->CacheAllForms( ex2[0].Question );
        }
    }

    return ex;
}
