
#ifndef MODEL_H
#define MODEL_H

#include "model_global.h"
#include <QStringList>
#include <QHash>

class MODEL_API Model
{
public:
    Model();
    ~Model();

    bool Load( const QString& );
    bool Add( const QString& );
    bool HasLine( const QString& ) const;

    static QString Simplify( const QString& );

    uint Size() const;

private:
    QStringList myLines;
    QHash<uint, uint> myHashes;
};

#endif // MODEL_H
