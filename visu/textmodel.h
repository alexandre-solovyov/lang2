#ifndef TEXTMODEL_H
#define TEXTMODEL_H

#include <QAbstractListModel>
#include <QQuickItem>
#include <model/StdModel.h>

class WordInfo
{
public:
  WordInfo(QString theText="", QString theTranslation="", bool isWord=false, bool isKnown=false);

  QString Text;
  QString Translation;
  bool IsWord;
  bool IsKnown;
};

class TextModel: public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(int nbUnknown READ nbUnknown NOTIFY nbUnknownChanged)

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

    QString fileName() const;
    void setFileName(QString theFileName);

    int nbUnknown() const;

    Q_INVOKABLE void select(QQuickItem*);
    Q_INVOKABLE QQuickItem* selectedItem() const;
    Q_INVOKABLE QString translation(QString theWord) const;
    Q_INVOKABLE void setAsKnownCpp(QString theWord);

signals:
    void fileNameChanged(QString theFileName);
    void nbUnknownChanged(int nbUnknowns);

protected:
    bool load();
    void setText(QString theText);
    WordInfo generate(QString theText, bool isWord) const;
    bool isKnown(QString theWord) const;

private:
    QList<WordInfo> myItems;
    QString         myProgressDir;
    QString         myTextDir;
    QString         myFileName;
    StdModel*       myModel;
    QQuickItem*     myCurrent;
    int             myNbUnknown;
};

#endif // TEXTMODEL_H
