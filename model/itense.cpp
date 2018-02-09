
#include <model/itense.h>

ITense::ITense( const QString& theName )
    : myName( theName )
{
}

ITense::~ITense()
{
}

QString ITense::Name() const
{
    return myName;
}
