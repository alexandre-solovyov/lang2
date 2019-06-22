
#include "wordslist.h"

/**
 * @brief WordInfo::WordInfo
 * Constructor
 * @param theText the text of the word
 * @param theTranslation the translation
 * @param isWord if the text corresponds to a word
 * @param isKnown if the word is known
 */
WordInfo::WordInfo(QString theText, QString theTranslation, bool isWord, bool isKnown)
    : Text(theText), Translation(theTranslation), IsWord(isWord), IsKnown(isKnown)
{
}

WordsList::WordsList()
    : myTrim(false), myLimit(0), myNbWords(0)
{
}

void WordsList::setTrim(bool trim)
{
    if (myTrim == trim)
        return;

    myTrim = trim;
}

void WordsList::setLimit(int limit)
{
    if (myLimit == limit)
        return;

    myLimit = limit;
}

bool WordsList::trim() const
{
    return myTrim;
}

int WordsList::limit() const
{
    return myLimit;
}

void WordsList::append(WordInfo theWordInfo)
{
    bool canAppend = !myTrim;
    canAppend = canAppend || (myNbWords>0 && myNbWords<myLimit);
    canAppend = canAppend || (myNbWords==0 && theWordInfo.IsWord && !theWordInfo.IsKnown);

    if(canAppend)
    {
        QList<WordInfo>::append(theWordInfo);
        if(theWordInfo.IsWord)
            myNbWords++;
    }
}

int WordsList::nbUnknown() const
{
    int aNbUnknown = 0;
    foreach(const WordInfo& anInfo, *this)
        if(anInfo.IsWord && !anInfo.IsKnown)
            aNbUnknown++;
    return aNbUnknown;
}
