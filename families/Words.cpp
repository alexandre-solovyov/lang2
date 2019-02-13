
#include <Words.h>
#include <QFileInfo>
#include <QSet>
#include <QString>
#include <QTime>
#include <iostream>

bool WordInfo::operator < (const WordInfo& theInfo) const
{
    return strcmp(word, theInfo.word) < 0;
}

bool Words::Load(const QString& theFilePath)
{
    QTime timer;
    timer.start();

    QFile aFile(theFilePath);
    if( !aFile.open( QIODevice::ReadOnly ) )
        return false;

    int aSize = QFileInfo(aFile).size() / sizeof(WordInfo);
    resize(aSize);

    aFile.read((char*)data(), size()*sizeof(WordInfo));
    aFile.close();

    std::cout << "Words loading time: " << timer.elapsed() << " ms" << std::endl;
    return true;
}

bool Words::Save(const QString& theFilePath) const
{
    QTime timer;
    timer.start();

    QFile aFile(theFilePath);
    if( !aFile.open( QIODevice::WriteOnly ) )
        return false;

    aFile.write((char*)data(), size()*sizeof(WordInfo));
    aFile.close();

    std::cout << "Words saving time: " << timer.elapsed() << " ms" << std::endl;
    return true;
}

QStringList Words::Initial(const QString& theWord) const
{
    QStringList anInitial;

    std::string s = theWord.toStdString();
    WordInfo wi;
    strcpy(wi.word, s.c_str());
    const_iterator it = std::lower_bound(begin(), end(), wi);
    if(strcmp(it->word, s.c_str())==0)
    {
        for(int j=0; j<MAX_INDICES; j++)
        {
            int ind = it->base_index[j];
            if(ind > 0)
            {
                std::string init(at(ind).word);
                anInitial.append(QString::fromStdString(init));
            }
        }
    }

    return anInitial;
}

QStringList Words::CheckText( const QString& thePath ) const
{
    QTime timer;
    timer.start();

    QSet<QString> unique;

    QFile aFile( thePath );
    if( !aFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        return QStringList();
    }

    QString aData = aFile.readAll();
    QStringList words = aData.split( QRegExp("\\W+"), QString::SkipEmptyParts );

    foreach( QString w, words )
    {
        w = w.toLower();
        QStringList forms = Initial(w);
        foreach(QString f, forms)
            unique.insert(f);
    }

    QList<QString> initials = unique.toList();
    qSort(initials);

    std::cout << "Text analysis time: " << timer.elapsed() << " ms" << std::endl;
    return initials;
}
