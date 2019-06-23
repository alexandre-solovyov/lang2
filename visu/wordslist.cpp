
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

/**
 * @brief WordsList::WordsList
 * Constructor
 */
WordsList::WordsList()
    : myTrim(false), myLimit(0), myNbWords(0)
{
}

/**
 * @brief WordsList::trim
 * Get if the list applies trimming
 * @return if the list applies trimming
 */
bool WordsList::trim() const
{
    return myTrim;
}

/**
 * @brief WordsList::setTrim
 * Set if the list applies trimming
 * @param isTrim if the trimming should be applied
 */
void WordsList::setTrim(bool isTrim)
{
    if (myTrim == isTrim)
        return;

    myTrim = isTrim;
}

/**
 * @brief WordsList::limit
 * Get the limit of included words
 * @return the limit of included words
 */
int WordsList::limit() const
{
    return myLimit;
}

/**
 * @brief TextModel::setLimit
 * Change the limit of included words
 * @param theLimit the new limit of included words
 */
void WordsList::setLimit(int theLimit)
{
    if (myLimit == theLimit)
        return;

    myLimit = theLimit;
}

/**
 * @brief WordsList::append
 * Append a new word information to the list
 * @param theWordInfo the word information to append
 */
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

/**
 * @brief WordsList::nbUnknown
 * Get number of unknown words in the list
 * @return the number of unknown words
 */
int WordsList::nbUnknown() const
{
    int aNbUnknown = 0;
    foreach(const WordInfo& anInfo, *this)
        if(anInfo.IsWord && !anInfo.IsKnown)
            aNbUnknown++;
    return aNbUnknown;
}
