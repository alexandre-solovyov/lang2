
#ifndef DB_READER_H
#define DB_READER_H

#include <QStringList>

class QXmlStreamReader;
class Rules;

class DbReader
{
public:
    DbReader( const QString& theFileName, int theLimit, int theErrLimit, int isVerbose );
    ~DbReader();

    bool Perform( Rules* );
    int Count() const;
    QStringList Errors() const;

private:
    void PerformVerbs( QXmlStreamReader& );
    void PerformVerb( QXmlStreamReader& );
    void PerformData( const QString&, const QString& );

private:
    QString myFileName;
    int     myLimit;
    int     myErrLimit;
    int     myCount;
    Rules*  myRules;
    int     myIsVerbose;
    QString myWP;
    QStringList myErrors;
};

#endif  // DB_READER_H
