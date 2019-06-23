#include "helper.h"
#include <QDir>
#include <QDebug>

/**
 * @brief Helper::Helper
 * Constructor
 * @param theParent the parent object
 */
Helper::Helper(QObject* theParent)
    : QObject(theParent)
{
}

/**
 * @brief Helper::~Helper
 * Destructor
 */
Helper::~Helper()
{
    flush(false);
}

/**
 * @brief Helper::path
 * Get the controlled folder's path
 * @return the controlled folder's path
 */
QString Helper::path() const
{
    return myPath;
}

/**
 * @brief Helper::setPath
 * Change the controlled path
 * @param thePath the new controlled path
 */
void Helper::setPath(QString thePath)
{
    qDebug() << "Helper::setPath" << thePath;
    if (myPath == thePath)
        return;

    myPath = thePath;
    myFiles.clear();
    QDir aDir(myPath);
    myFiles = aDir.entryList(QStringList() << "*.lang");
    myFiles.append("private");
    qDebug() << myFiles;

    flush(true);
    qDebug() << myData.keys();
    emit pathChanged(myPath);
    emit categoriesChanged(myData.keys());
}

/**
 * @brief Helper::categories
 * Get the categories (corresponding to files)
 * @return the categories
 */
QStringList Helper::categories() const
{
    return myData.keys();
}

/**
 * @brief Helper::flush
 * Synchronize the internal (memory) data structures with the files contents
 * @param isLoad if the data should be loaded (true) or saved (false)
 */
void Helper::flush(bool isLoad)
{
    if(isLoad)
        myData.clear();

    foreach(QString aFileName, myFiles)
    {
        QString aCategory = category(aFileName);
        FileData& aFileData = myData[aCategory];
        QFile aFile( myPath + "/" + aFileName );
        QFile::OpenMode aMode = (isLoad ? QIODevice::ReadOnly : QIODevice::WriteOnly)
                | QIODevice::Text;
        if(isLoad)
        {
            if( aFile.open(aMode) )
            {
                QString aTextData = aFile.readAll();
                aFileData.Lines = aTextData.split("\n", QString::KeepEmptyParts);
                aFileData.Modified = false;
                aFile.close();
            }
        }
        else
        {
            if(aFileData.Modified)
            {
                if( aFile.open(aMode) )
                {
                    QString aTextData = aFileData.Lines.join("\n");
                    aFile.write(aTextData.toUtf8());
                    aFile.close();
                }
            }
        }
    }
}

/**
 * @brief Helper::category
 * Determine the name of category on the base of name of file
 * @param theFileName the name of the file
 * @return the category's name
 */
QString Helper::category(QString theFileName) const
{
    QStringList parts = theFileName.split(".", QString::KeepEmptyParts);
    QString aCategory;
    if(parts.size()==3)
        aCategory = parts[1];
    else if(parts.size()==1)
        aCategory = parts[0];
    return aCategory;
}

/**
 * @brief Helper::isSorted
 * Determine if the category is sorted
 * @param theCategory the name of the category
 * @return if the category is sorted
 */
bool Helper::isSorted(QString theCategory) const
{
    return theCategory=="adjectives" || theCategory=="verbs"
            || theCategory=="adverbs"
            || (theCategory=="nouns" && myLanguage!="de")
            ;
}

/**
 * @brief Helper::insert
 * Insert a new line into a category
 * @param theIndex the category's index
 * @param theWord the new word to insert
 * @param theTranslation the translation of the word
 */
void Helper::insert(int theIndex, QString theWord, QString theTranslation)
{
    //qDebug() << theIndex << theWord << theTranslation;

    QString aCategory = categories()[theIndex];
    if(aCategory=="private")
        theTranslation = "";

    QString aNewLine = theWord;
    if(!theTranslation.isEmpty())
        aNewLine = aNewLine + " = " + theTranslation;

    FileData& fdata = myData[aCategory];
    QStringList& data = fdata.Lines;
    fdata.Modified = true;

    if(isSorted(aCategory))
    {
        QString prev;
        for(int i=0, n=data.size(); i<n; i++)
        {
            QString cur = data[i];
            if(cur.contains('='))
            {
                if(!prev.isEmpty() && prev < cur && aNewLine > prev && aNewLine < cur)
                {
                    data.insert(i, aNewLine);
                    return;
                }
                prev = cur;
            }
        }
        data.append(aNewLine);
    }
    else
    {
        int anIndex = data.size();
        if( anIndex>0 && data[anIndex-1].isEmpty() )
            anIndex--;
        data.insert(anIndex, aNewLine);
    }
}

/**
 * @brief Helper::language
 * Get the associated language
 * @return the associated language
 */
QString Helper::language() const
{
    return myLanguage;
}

/**
 * @brief Helper::setLanguage
 * Change the associated language
 * @param theLanguage the new associated language
 */
void Helper::setLanguage(QString theLanguage)
{
    qDebug() << "Helper::setLanguage";

    if (myLanguage == theLanguage)
        return;

    myLanguage = theLanguage;
    QString anExtLanguage = Helper::extLanguage(myLanguage);
    setPath("../lang/progress/" + anExtLanguage);
    emit languageChanged(myLanguage);
}

/**
 * @brief Helper::extLanguage
 * Determine the extended language name from its code
 * @param theLanguage the language code
 * @return the extended language name
 */
QString Helper::extLanguage(QString theLanguage)
{
    static QMap<QString, QString> languageCodes;
    if(languageCodes.isEmpty())
    {
        languageCodes["en"] = "english";
        languageCodes["fr"] = "french";
        languageCodes["de"] = "german";
    }

    if(languageCodes.contains(theLanguage))
        return languageCodes[theLanguage];
    else
        return theLanguage;
}
