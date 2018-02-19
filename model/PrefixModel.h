
#ifndef PREFIX_MODEL_H
#define PREFIX_MODEL_H

#include <model/model_global.h>
#include <QStringList>
#include <QMap>

/**
  @class PrefixModel
  @brief The class for universal prefixes model
*/
class MODEL_API PrefixModel
{
public:
    PrefixModel();
    ~PrefixModel();

    bool Add( const QString& );
    uint Size() const;
    QStringList Starts( const QString& ) const;

    bool Match( const QString& theWord, const QString& thePrefix ) const;

private:
    bool IsEqual( const QString& theStart, const QString& theWordPart ) const;

private:
    typedef QMap<QString, QStringList> Prefixes;  ///< the type definition for prefixes map
    Prefixes myPrefixes;                          ///< the prefixes map
};

#endif // PREFIX_MODEL_H
