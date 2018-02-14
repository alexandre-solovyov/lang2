
#ifndef LANG_FILE_H
#define LANG_FILE_H

#include <model/model_global.h>
#include <model/exercise.h>
#include <model/igenerator.h>
#include <QStringList>
#include <QHash>

class MODEL_API LangFile
{
public:
    LangFile();
    ~LangFile();

    bool Load( const QString&, bool isVerbose=false );

    uint AddFile( const QString& );
    bool Add( uint theFileIndex, const QString& );
    bool HasLine( const QString& ) const;

    uint NbLines() const;

    ListOfExercises Build( const QList<IGenerator*>&, bool isVerbose=false );

private:
    static QString Simplify( const QString& );
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

#endif // LANG_FILE_H
