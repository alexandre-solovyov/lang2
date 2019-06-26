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
    bool isSortable = true;

    myGroups.clear();
    foreach(QString aLine, theLines)
    {
        if(aLine.isEmpty())
        {
            appendGroup(aGroup, isSortable);
            aGroup.clear();
            isSortable = true;
        }
        else
        {
            aGroup.append(aLine);
            if(aLine.contains('[') || aLine.contains('~') || aLine.contains('~'))
                isSortable = false;
        }
    }
    appendGroup(aGroup, isSortable);
}

void SortTool::appendGroup(const QStringList& theGroup, const bool isSortable)
{
    if(!theGroup.isEmpty())
    {
        Group aGroup;
        aGroup.Lines = theGroup;
        aGroup.IsSortable = isSortable;
        myGroups.append(aGroup);
    }
}

QString SortTool::join() const
{
    QString aResult;
    foreach(const Group& aGroup, myGroups)
    {
        aResult += aGroup.Lines.join("\n");
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

QChar Std(const QChar& c, const QString& s)
{
    if(c>='a' && c<='z')
        return c;
    if(c>=u'а' && c<=u'я')
        return c;
    if(c.isSpace() || c=='/' || c=='!' || c=='=')
        return c;

    if(c==u'é' || c==u'ê' || c==u'è')
        return 'e';
    if(c==u'î')
        return 'i';

    qDebug() << "Special not treated:" << QString(c) << s;
    return c;
}

bool compareWords(const QString& theFirst, const QString& theSecond)
{
    QString aFirst = theFirst;
    clean(aFirst);
    QString aSecond = theSecond;
    clean(aSecond);
    //qDebug() << aFirst << aSecond;

    for(int i=0, n=qMin(aFirst.size(), aSecond.size()); i<n; i++)
    {
        QChar c1 = Std(aFirst[i], aFirst);
        QChar c2 = Std(aSecond[i], aSecond);
        if(c1 < c2)
            return true;
        else if(c1 > c2)
            return false;
    }

    return aFirst.size() < aSecond.size();
}

void SortTool::sort()
{
    for(int i=0, n=myGroups.size(); i<n; i++)
        if(myGroups[i].IsSortable)
            std::sort(myGroups[i].Lines.begin(), myGroups[i].Lines.end(), compareWords);
}
