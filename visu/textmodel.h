#ifndef TEXTMODEL_H
#define TEXTMODEL_H

#include <QAbstractListModel>
#include <QQuickItem>
#include <model/StdModel.h>
#include <wordslist.h>

class TextModel: public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(int nbUnknown READ nbUnknown NOTIFY nbUnknownChanged)
    Q_PROPERTY(bool trim READ trim WRITE setTrim NOTIFY trimChanged)
    Q_PROPERTY(int limit READ limit WRITE setLimit NOTIFY limitChanged)

public:
    enum Roles
    {
        FirstNotUsed = Qt::UserRole,
        TranslationRole,
        IsWordRole,
        IsKnownRole,
    };

    TextModel(QObject* theParent = nullptr);
    virtual ~TextModel() override;

    virtual int rowCount(const QModelIndex &theParent) const override;
    virtual QVariant data(const QModelIndex &theIndex, int theRole) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    int nbUnknown() const;

    QString fileName() const;
    void setFileName(QString theFileName);
    QString progressPath() const;
    void setProgressPath(QString progressPath);
    QString textPath() const;
    void setTextPath(QString textPath);
    QString language() const;
    void setLanguage(QString language);
    bool trim() const;
    void setTrim(bool trim);
    int limit() const;
    void setLimit(int limit);

    Q_INVOKABLE bool load();
    Q_INVOKABLE void select(QQuickItem*);
    Q_INVOKABLE QQuickItem* selectedItem() const;
    Q_INVOKABLE QString translation(QString theWord) const;
    Q_INVOKABLE void setAsKnownCpp(QString theWord);

signals:
    void fileNameChanged(QString theFileName);
    void nbUnknownChanged(int nbUnknowns);
    void progressPathChanged(QString progressPath);
    void textPathChanged(QString textPath);
    void languageChanged(QString language);
    void trimChanged(bool trim);
    void limitChanged(int limit);

protected:
    void setText(QString theText);
    WordInfo generate(QString theText, bool isWord) const;
    bool isKnown(QString theWord) const;

private:
    WordsList       myItems;
    QString         myProgressPath;
    QString         myTextPath;
    QString         myFileName;
    StdModel*       myModel;
    QQuickItem*     myCurrent;
    int             myNbUnknown;
    QString         myLanguage;
};

#endif // TEXTMODEL_H
