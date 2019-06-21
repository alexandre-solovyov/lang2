#ifndef HELPER_H
#define HELPER_H

#include <QObject>
#include <QMap>

class Helper : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QStringList categories READ categories NOTIFY categoriesChanged)

public:
    explicit Helper(QObject* theParent = nullptr);
    virtual ~Helper();

    QString path() const;
    void setPath(QString thePath);
    QStringList categories() const;

    Q_INVOKABLE void insert(int theIndex, QString theWord, QString theTranslation);

signals:
    void pathChanged(QString thePath);
    void categoriesChanged(QStringList categories);

protected:
    QString category(QString theFileName) const;
    bool isSorted(QString theCategory) const;
    void flush(bool isLoad);

private:
    QString myPath;
    QStringList myFiles;
    QMap<QString, QStringList> myData;
    QStringList m_categories;
};

#endif // HELPER_H
