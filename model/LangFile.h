
#ifndef LANG_FILE_H
#define LANG_FILE_H

#include <model/model_global.h>
#include <model/Exercise.h>
#include <model/IGenerator.h>
#include <QStringList>
#include <QHash>

/**
  @class LangFile
  @brief The class for work with language format file
*/
class MODEL_API LangFile
{
public:
    LangFile();
    ~LangFile();

    bool Load( const QString&, bool isVerbose=false );

    uint AddFile( const QString& );
    bool Add( uint theFileIndex, const QString& );
    bool HasLine( uint theFileIndex, const QString& ) const;

    uint NbLines() const;

    ListOfExercises Build( const QList<IGenerator*>&, bool isVerbose=false );

private:
    void ChangeContext( Context& theContext,
                        const QString& theKey,
                        const QString& theValue,
                        const QList<IGenerator*>& theGenerators ) const;
    QString ExtractTag( QString& theLine ) const;

private:
    /**
      @struct FileData
      @brief The internal information about loaded files and lines
    */
    struct FileData
    {
      QString Name;       ///< the loaded file's name
      QStringList Lines;  ///< the loaded lines
    };

    QList<FileData> myFiles;              ///< the loaded files
    QList<QHash<uint, uint> > myHashes;   ///< the hashes of loaded lines
};

#endif // LANG_FILE_H
