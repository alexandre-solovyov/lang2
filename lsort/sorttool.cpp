#include "sorttool.h"
#include <QDebug>
#include <QFile>

SortTool::SortTool()
{
}

SortTool::~SortTool()
{
}

bool SortTool::perform(QString theFileName)
{
    if(!load(theFileName))
        return false;

    sort();
    return save(theFileName);
}

bool SortTool::load(QString theFileName)
{
    qDebug() << "Loading:" << theFileName;

    QFile aFile(theFileName);
    bool isOK = aFile.open(QIODevice::ReadOnly | QIODevice::Text);
    if(isOK)
    {
        QStringList lines = QString(aFile.readAll()).split("\n", QString::KeepEmptyParts);
        split(lines);
        qDebug() << "Nb groups:" << myGroups.size();
        aFile.close();
    }
    return isOK;
}

bool SortTool::save(QString theFileName)
{
    qDebug() << "Saving: " << theFileName;

    QFile aFile(theFileName);
    bool isOK = aFile.open(QIODevice::WriteOnly | QIODevice::Text);
    if(isOK)
    {
        QString aTextData = join();
        aFile.write(aTextData.toUtf8());
        aFile.close();
    }
    return isOK;
}

void SortTool::split(const QStringList& theLines)
{
    QStringList aGroup;

    myGroups.clear();
    foreach(QString aLine, theLines)
    {
        if(aLine.isEmpty())
        {
            appendGroup(aGroup);
            aGroup.clear();
        }
        else
            aGroup.append(aLine);
    }
    appendGroup(aGroup);
}

void SortTool::appendGroup(const QStringList& theGroup)
{
    if(!theGroup.isEmpty())
        myGroups.append(theGroup);
}

QString SortTool::join() const
{
    QString aResult;
    foreach(const QStringList& aGroup, myGroups)
    {
        aResult += aGroup.join("\n");
        aResult += "\n\n";
    }
    aResult = aResult.trimmed();
    aResult += "\n";
    return aResult;
}

void remove(QString& theWord, const QStringList& theParts)
{
    foreach(QString aPart, theParts)
        theWord = theWord.remove(aPart);
}

void clean(QString& theWord)
{
    static QStringList COMMON = QStringList() << "*";
    static QStringList FR_ARTICLES = QStringList() << "une " << "un " << "des ";
    static QStringList FR_PREPOSITIONS = QStringList() << "en ";

    theWord = theWord.toLower();
    remove(theWord, COMMON);
    remove(theWord, FR_ARTICLES);
    remove(theWord, FR_PREPOSITIONS);

    theWord = theWord.trimmed();
}

bool compareWords(const QString& theFirst, const QString& theSecond)
{
    QString aFirst = theFirst;
    clean(aFirst);
    QString aSecond = theSecond;
    clean(aSecond);
    //qDebug() << aFirst << aSecond;
    return aFirst < aSecond;
}

void SortTool::sort()
{
    for(int i=0, n=myGroups.size(); i<n; i++)
        std::sort(myGroups[i].begin(), myGroups[i].end(), compareWords);
}
