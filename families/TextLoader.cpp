
#include <TextLoader.h>
#include <Words.h>
#include <QFile>
#include <QList>
#include <QSet>
#include <QTime>
#include <iostream>

bool TextLoader::Load(const QString& thePath)
{
    QTime timer;
    timer.start();

    std::cout << thePath.toStdString() << std::endl;

    QFile aFile(thePath);
    if( !aFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
        return false;

    QString aData = aFile.readAll();
    QStringList lines = aData.split( "\n", QString::SkipEmptyParts );
    aFile.close();

    std::cout << "Nb lines: " << lines.size() << std::endl;
    QString aBase;
    foreach(QString aLine, lines)
    {
        if( aLine.isEmpty() )
            continue;

        bool isTab = aLine[0]=='\t';

        QString aTLine = aLine.trimmed();
        if( isTab )
            myFamilies[aTLine] = aBase;
        else
            aBase = aTLine;
    }

    std::cout << "Load time: " << timer.elapsed() << " ms" << std::endl;
    return true;
}

int TextLoader::CalcMaxLength(QString* theArg) const
{
    int max = 0;
    QMap<QString, QString>::const_iterator it = myFamilies.begin(), last = myFamilies.end();
    for( ; it!=last; ++it )
    {
        int len1 = it.key().length();
        int len2 = it.value().length();
        int len = qMax(len1, len2);
        if( len > max )
        {
            max = len;
            if( theArg )
                *theArg = it.key();
        }
    }
    return max;
}

void TextLoader::ConvertToWords(Words& theWords) const
{
    QTime timer;
    timer.start();

    QSet<QString> unique_words;
    QMap<QString, QString>::const_iterator it = myFamilies.begin(), last = myFamilies.end();
    for( ; it!=last; ++it )
    {
        unique_words.insert(it.key());
        unique_words.insert(it.value());
    }

    QList<QString> words_list = unique_words.toList();
    qSort(words_list);

    int n = words_list.size();
    theWords.resize(n);
    for( int i=0; i<n; i++ )
    {
        std::string aWord = words_list[i].toStdString();
        strcpy(theWords[i].word, aWord.c_str());
        for(int j=0; j<MAX_INDICES; j++)
            theWords[i].base_index[j] = 0;
    }

    it = myFamilies.begin(); last = myFamilies.end();
    for( ; it!=last; ++it )
    {
        QList<QString>::const_iterator itf1 = qBinaryFind(words_list.begin(), words_list.end(), it.key());
        int index1 = itf1 - words_list.begin();

        QList<QString>::const_iterator itf2 = qBinaryFind(words_list.begin(), words_list.end(), it.value());
        int index2 = itf2 - words_list.begin();

        theWords[index1].base_index[0] = index2;
    }

    std::cout << "Conversion time: " << timer.elapsed() << " ms" << std::endl;
}
