#ifndef HELPER_H
#define HELPER_H

#include <QObject>
#include <QMap>

class Helper : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QStringList categories READ categories)

public:
    explicit Helper(QObject* theParent = nullptr);
    virtual ~Helper();

    QString path() const;
    void setPath(QString thePath);
    QStringList categories() const;

signals:
    void pathChanged(QString thePath);

protected:
    QString category(QString theFileName) const;
    void flush(bool isLoad);

private:
    QString myPath;
    QStringList myFiles;
    QMap<QString, QStringList> myData;
};

#endif // HELPER_H
