
#include <model/ITense.h>
#include <model/Grammar.h>

/**
  @brief Constructor
  @param theName the tense's name
  @param theGrammar the associated grammar
*/
ITense::ITense( const QString& theName, Grammar* theGrammar )
    : myName( theName ), myGrammar( theGrammar )
{
    if( theGrammar )
        theGrammar->Add( this );
}

/**
  @brief Destructor
*/
ITense::~ITense()
{
}

/**
  @brief Get the tense's name
  @return the tense's name
*/
QString ITense::Name() const
{
    return myName;
}

/**
  @brief Get the associated grammar
  @return the associated grammar
*/
Grammar* ITense::grammar() const
{
    return myGrammar;
}

void ITense::setGrammar( Grammar* theGrammar )
{
    myGrammar = theGrammar;
}

bool ITense::Unite( ITense* )
{
    // On the basic level the implementation is empty
    return true;
}
