
#include <model/EG_Forms.h>
#include <model/Tools.h>
#include <model/Grammar.h>
#include <model/StdTense.h>

const QString FORMS_MARK = ">>";

/**
  @brief Constructor
  @param theGrammar the associated grammar
*/
EG_Forms::EG_Forms( Grammar* theGrammar, bool isCopyTenses )
    : EG_Trans(false, true), myGrammar( theGrammar ), myIsCopyTenses( isCopyTenses )
{
}

/**
  @brief Destructor
*/
EG_Forms::~EG_Forms()
{
}

/**
*/
QString EG_Forms::Type() const
{
    return "forms";
}

/**
*/
void EG_Forms::Reset()
{
    if( myIsCopyTenses )
        CopyTenses();
    else
        DeleteTenses();

    myTenses.clear();
    myIgnore.clear();
}

/**
*/
void EG_Forms::Ignore( const QStringList& theIgnore )
{
    myIgnore = theIgnore;
}

/**
*/
ListOfExercises EG_Forms::Generate( const QString& theLine, const Context& theContext, bool& isOtherProduct ) const
{
    isOtherProduct = false;
    ListOfExercises ex;

    if( theLine.contains( FORMS_MARK ) )
    {
        if( myGrammar )
        {
            //Tools::print( theLine );
            //Tools::print( theContext.Tag );
            if( !myTenses.contains( theContext.Tag ) )
                const_cast<EG_Forms*>( this )->myTenses[theContext.Tag] = new StdTense( theContext.Tag, 0 );
            isOtherProduct = true;

            StdTense* tense = dynamic_cast<StdTense*>( myTenses[theContext.Tag] );
            GrammarRule gr = tense->Add( theLine );
            if( gr.IsSingle() )
            {
                myGrammar->CacheAllForms( gr.Start(), tense );
                //Tools::print( theRule );
            }
        }

        return ex;
    }

    if( theLine.contains( EQ_MARK ) )
    {
        ListOfExercises ex2 = EG_Trans::Generate( theLine, theContext, isOtherProduct );
        isOtherProduct = false;
        if( ex2.length() == 1 )
        {
            //Tools::print( ex2[0].Question );
            //TODO: support multi-word forms (?)
            QString w = ex2[0].Question;
            foreach( QString i, myIgnore )
                w = w.replace( i, "" );
            w = w.trimmed();
            //Tools::print( "before forms: " + w );
            QMap<QString, StdTense*>::const_iterator it = myTenses.begin(), last = myTenses.end();
            for( ; it!=last; ++it )
                myGrammar->CacheAllForms( w, it.value() );
        }
    }

    return ex;
}

void EG_Forms::CopyTenses()
{
    if( myGrammar )
    {
        QMap<QString, StdTense*>::const_iterator it = myTenses.begin(), last = myTenses.end();
        for( ; it!=last; ++it )
            myGrammar->Add(it.value());
    }
}

void EG_Forms::DeleteTenses()
{
    QMap<QString, StdTense*>::const_iterator it = myTenses.begin(), last = myTenses.end();
    for( ; it!=last; ++it )
        delete it.value();
}
