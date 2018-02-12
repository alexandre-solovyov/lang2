
#include <model/itense.h>
#include <model/grammar.h>

ITense::ITense( const QString& theName, Grammar* theGrammar )
    : myName( theName ), myGrammar( theGrammar )
{
    if( theGrammar )
        theGrammar->Add( this );
}

ITense::~ITense()
{
}

QString ITense::Name() const
{
    return myName;
}

Grammar* ITense::grammar() const
{
    return myGrammar;
}
