#include "helper.h"
#include <QDir>
#include <QDebug>

Helper::Helper(QObject* theParent)
    : QObject(theParent)
{
}

Helper::~Helper()
{
    flush(false);
}

QString Helper::path() const
{
    return myPath;
}

QStringList Helper::categories() const
{
    return myData.keys();
}

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

void Helper::flush(bool isLoad)
{
    if(isLoad)
        myData.clear();

    foreach(QString aFileName, myFiles)
    {
        QString aCategory = category(aFileName);
        QStringList& aFileData = myData[aCategory];
        QFile aFile( myPath + "/" + aFileName );
        QFile::OpenMode aMode = (isLoad ? QIODevice::ReadOnly : QIODevice::WriteOnly)
                                | QIODevice::Text;
        if( aFile.open(aMode) )
        {
            if(isLoad)
            {
                QString aTextData = aFile.readAll();
                aFileData = aTextData.split("\n", QString::KeepEmptyParts);
            }
            else {
                QString aTextData = aFileData.join("\n");
                aFile.write(aTextData.toUtf8());
            }
            aFile.close();
        }
        myData[aCategory] = aFileData;
    }
}

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

bool Helper::isSorted(QString theCategory) const
{
    return theCategory=="adjectives" || theCategory=="verbs" || (theCategory=="nouns" && myLanguage!="de");
}

void Helper::insert(int theIndex, QString theWord, QString theTranslation)
{
    //qDebug() << theIndex << theWord << theTranslation;

    QString aCategory = categories()[theIndex];
    if(aCategory=="private")
        theTranslation = "";

    QString aNewLine = theWord;
    if(!theTranslation.isEmpty())
        aNewLine = aNewLine + " = " + theTranslation;
    QStringList& data = myData[aCategory];
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
                    break;
                }
                prev = cur;
            }
        }
    }
    else
    {
        int anIndex = data.size();
        if( anIndex>0 && data[anIndex-1].isEmpty() )
            anIndex--;
        data.insert(anIndex, aNewLine);
    }
}

QString Helper::language() const
{
    return myLanguage;
}

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
