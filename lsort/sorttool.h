#ifndef SORTTOOL_H
#define SORTTOOL_H

#include <QStringList>

class SortTool
{
public:
    SortTool();
    ~SortTool();

    bool perform(QString theFileName);

protected:
    bool load(QString theFileName);
    void sort();
    bool save(QString theFileName);

    void split(const QStringList&);
    QString join() const;
    void appendGroup(const QStringList&);

private:
    QList<QStringList> myGroups;
};

#endif // SORTTOOL_H
