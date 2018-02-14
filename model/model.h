
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

    bool Load( const QString&, bool isVerbose=false );

    int  AddFile( const QString& );
    bool Add( int theFileIndex, const QString& );
    bool HasLine( const QString& ) const;

    static QString Simplify( const QString& );

    uint Size() const;

    ListOfExercises Build( const QList<IGenerator*>&, bool isVerbose=false );

private:
    void ChangeContext( Context& theContext, const QString& theKey, const QString& theValue ) const;
    QString ExtractTag( QString& theLine ) const;

private:
    struct FileData
    {
      QString Name;
      QStringList Lines;
    };

    QList<FileData> myFiles;
    QHash<uint, uint> myHashes;
};

#endif // MODEL_H
