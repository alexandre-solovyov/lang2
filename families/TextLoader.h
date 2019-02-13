
#pragma once

#include <QMap>
#include <QString>

class Words;

class TextLoader
{
public:
    bool Load( const QString& theFilePath );
    int CalcMaxLength( QString* theArg = 0 ) const;

    void ConvertToWords(Words&) const;

private:
    QMap<QString, QString> myFamilies;
};
