
#pragma once

#include <vector>
#include <QStringList>

const int MAX_LEN = 27;
const int MAX_INDICES = 2;

struct WordInfo
{
    char word[MAX_LEN+1];
    int  base_index[MAX_INDICES];

    bool operator < (const WordInfo&) const;
};

class Words : public std::vector<WordInfo>
{
public:
    bool Load(const QString&);
    bool Save(const QString&) const;

    QStringList Initial(const QString&) const;
    QStringList CheckText( const QString& thePath ) const;
};
