
#ifndef ITENSE_H
#define ITENSE_H

class QString;
class GrammarSet;

class ITense
{
public:
    virtual GrammarSet Forms( const QString& theWord ) const = 0;
};

#endif // ITENSE_H
