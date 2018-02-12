
#ifndef MODEL_H
#define MODEL_H

#include <model/model_global.h>
#include <model/exercise.h>
#include <model/igenerator.h>
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

    ListOfExercises Build( const QList<IGenerator*>& );

private:
    void ChangeContext( Context& theContext, const QString& theKey, const QString& theValue );

private:
    QStringList myLines;
    QHash<uint, uint> myHashes;
};

#endif // MODEL_H
