
#ifndef STATISTICS_H
#define STATISTICS_H

#include <model/model_global.h>
#include <QHash>

class MODEL_API Statistics
{
public:
    Statistics();
    ~Statistics();

    void Add( const QString&, bool isCorrect );
    int NbCorrect( const QString& ) const;
    int NbIncorrect( const QString& ) const;
    double Weight( const QString& ) const;

private:
    int key( const QString& ) const;
    struct Data
    {
        int correct;
        int incorrect;
    };
    QHash<int, Data> myData;
};

#endif // STATISTICS_H
