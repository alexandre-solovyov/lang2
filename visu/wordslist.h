#ifndef WORDSLIST_H
#define WORDSLIST_H

#include <QString>
#include <QList>

class WordInfo
{
public:
    WordInfo(QString theText="", QString theTranslation="", bool isWord=false, bool isKnown=false);

    QString Text;
    QString Translation;
    bool IsWord;
    bool IsKnown;
};

class WordsList: public QList<WordInfo>
{
public:
    WordsList();

    void append(WordInfo);

    bool trim() const;
    void setTrim(bool trim);
    int limit() const;
    void setLimit(int limit);

    int nbUnknown() const;

private:
    bool myTrim;
    int  myLimit;
    int  myNbWords;
};

#endif // WORDSLIST_H
