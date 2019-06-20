#ifndef TEXTMODEL_H
#define TEXTMODEL_H

#include <QAbstractListModel>

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

    bool load(QString theFileName);
    void setText(QString theText);

signals:
    void fileNameChanged(QString theFileName);

private:
    QList<WordInfo> myItems;
    QString         myFileName;
};

#endif // TEXTMODEL_H
