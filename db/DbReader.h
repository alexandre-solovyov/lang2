
#ifndef DB_READER_H
#define DB_READER_H

#include <QString>

class QXmlStreamReader;
class Rules;

class DbReader
{
public:
    DbReader( const QString& theFileName, int theLimit, int theErrLimit, bool isVerbose );
    ~DbReader();

    bool Perform( Rules* );
    int Count() const;

private:
    void PerformVerbs( QXmlStreamReader& );
    void PerformVerb( QXmlStreamReader& );
    void PerformData( const QString&, const QString& );

private:
    QString myFileName;
    int     myLimit;
    int     myErrLimit;
    int     myCount;
    int     myErrorCount;
    Rules*  myRules;
    bool    myIsVerbose;
};

#endif  // DB_READER_H
