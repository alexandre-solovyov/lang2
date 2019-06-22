#include "textmodel.h"
#include <QDebug>
#include <QFile>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <model/Tools.h>
#include <helper.h>

static QRegExp WW("^\\w+");  ///< the regular expression for words
static QRegExp NW("^[\\W\\s]+");  ///< the regular expression for not-words

/**
 * @brief TextModel::TextModel
 * Constructor
 * @param theParent the parent object
 */
TextModel::TextModel(QObject* theParent)
    : QAbstractListModel(theParent), myModel(new StdModel()), myCurrent(nullptr), myNbUnknown(0)
{
}

/**
 * @brief TextModel::~TextModel
 * Destructor
 */
TextModel::~TextModel()
{
    delete myModel;
}

/**
 * @brief TextModel::rowCount
 * Get number of rows
 * @param theParent the parent index
 * @return the number of rows
 */
int TextModel::rowCount(const QModelIndex &theParent) const
{
    int rowCount = ( theParent.isValid() ? 0 : myItems.size() );
    //qDebug() << "Row count: " << rowCount;
    //qDebug() << "Items: " << myItems.size();
    return rowCount;
}

/**
 * @brief TextModel::data
 * Get data from the model corresponding to given role
 * @param theIndex the index
 * @param theRole the role
 * @return the associated data
 */
QVariant TextModel::data(const QModelIndex &theIndex, int theRole) const
{
    if(theIndex.isValid())
    {
        const WordInfo& anInfo = myItems[theIndex.row()];
        switch(theRole)
        {
        case Qt::DisplayRole:
            if(anInfo.Text=="<newline>")
                return "  ";
            else if(anInfo.Text=="<endline>")
                return "\r";
            else
                return anInfo.Text;
        case TranslationRole:
            return anInfo.Translation;
        case IsWordRole:
            return anInfo.IsWord;
        case IsKnownRole:
            return anInfo.IsKnown;
        }
    }
    return QVariant();
}

/**
 * @brief TextModel::roleNames
 * Get the names of roles in QML
 * @return the hash map of names of roles
 */
QHash<int, QByteArray> TextModel::roleNames() const
{
    static QHash<int, QByteArray> TYPES;
    if(TYPES.empty())
    {
        TYPES[Qt::DisplayRole] = "m_text";
        TYPES[TranslationRole] = "m_translation";
        TYPES[IsWordRole] = "m_isWord";
        TYPES[IsKnownRole] = "m_isKnown";
    }
    return TYPES;
}

/**
 * @brief TextModel::fileName
 * Get associated file name
 * @return the associated file name
 */
QString TextModel::fileName() const
{
    return myFileName;
}

/**
 * @brief TextModel::setFileName
 * Change the associated file name
 * @param theFileName the new file name
 */
void TextModel::setFileName(QString theFileName)
{
    qDebug() << "TextModel::setFileName" << theFileName;

    if (myFileName == theFileName)
        return;

    myFileName = theFileName;
    load();
    emit fileNameChanged(myFileName);
}

/**
 * @brief TextModel::load
 * Load the given file
 */
bool TextModel::load()
{
    if(myProgressPath.isEmpty() || myTextPath.isEmpty() || myFileName.isEmpty())
        return false;

    qDebug() << "TextModel::load()";

    // 1. Load the model's contents from language files
    myModel->Load( myProgressPath, myLanguage, true );
    myModel->LoadPrivate( myProgressPath + "/private" );

    qDebug() << QString("Nb exercises: %0").arg( myModel->NbExercises() );
    qDebug() << QString("Nb known: %0").arg( myModel->grammar().NbKnown() );

    // 2. Load a text file for analysis
    QString aFileName = myTextPath + "/" + myFileName;
    qDebug() << "Text for analysis:" << aFileName;
    QFile aFile( aFileName );
    if( !aFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
        return false;

    QString aData = aFile.readAll();
    aFile.close();
    setText(aData);
    return true;
}

/**
 * @brief TextModel::setText
 * Set the text for the analysis
 * @param theText the text to set
 */
void TextModel::setText(QString theText)
{
    qDebug() << "TextModel::setText";

    myItems.clear();
    myItems.append(WordInfo("<newline>"));
    QStringList items = theText.split("\n", QString::SkipEmptyParts);

    foreach(QString anItem, items)
    {
        while(!anItem.isEmpty())
        {
            //qDebug() << anItem;
            bool isLetter = anItem[0].isLetterOrNumber();
            QRegExp& anExpr = isLetter ? WW : NW;
            anItem.indexOf(anExpr);
            QString aPart = anExpr.cap(0);
            //qDebug() << aPart;
            anItem.remove(0, aPart.length());

            aPart = aPart.trimmed();
            if(!aPart.isEmpty())
            {
                WordInfo anInfo = generate(aPart, isLetter);
                myItems.append(anInfo);
            }
        }
        myItems.append(WordInfo("<endline>"));
        myItems.append(WordInfo("<newline>"));
    }

    myNbUnknown = myItems.nbUnknown();
    emit nbUnknownChanged(myNbUnknown);
}

/**
 * @brief TextModel::generate
 * Generate the word information by the given text
 * @param theText the text to analyze
 * @return the generated word information
 */
WordInfo TextModel::generate(QString theText, bool isWord) const
{
    //qDebug() << "generate for" << theText;
    QString aText = theText.toLower();
    if( Tools::startsWithDigit(aText) )
        return WordInfo(theText, "", isWord, true);

    QString aTranslation;
    bool known = isKnown(aText);
    return WordInfo(theText, aTranslation, isWord, known);
}

/**
 * @brief TextModel::isKnown
 * Determine if the given word is known in the model
 * @param theWord the word to analyze
 * @return if the word is known
 */
bool TextModel::isKnown(QString theWord) const
{
    bool isRussian = true;
    foreach(QChar c, theWord)
    {
        QChar cc = c.toLower();
        if(cc.isLetter() && !(cc>=u'а' && cc<=u'я'))
        {
            isRussian = false;
            break;
        }
    }
    if(isRussian)
        return true;

    QString init = myModel->grammar().Init(theWord).join(" ");
    bool known = myModel->grammar().IsKnown(init);
    return known;
}

/**
 * @brief TextModel::select
 * Select the given item
 * @param theItem the item to select
 */
void TextModel::select(QQuickItem* theItem)
{
    if(myCurrent)
        myCurrent->setProperty("selection", false);

    myCurrent = theItem;
    if(myCurrent)
        myCurrent->setProperty("selection", true);
}

/**
 * @brief TextModel::selectedItem
 * Get the selected item
 * @return the selected item
 */
QQuickItem* TextModel::selectedItem() const
{
    return myCurrent;
}

/**
 * @brief TextModel::translation
 * Get the translation of the word
 * @param theWord the word to translate
 * @return the found translation
 */
QString TextModel::translation(QString theWord) const
{
    QString aText = theWord.toLower();
    if( Tools::startsWithDigit(aText) )
        return theWord;

    QString init = myModel->grammar().Init(aText).join(" ");

    QString aResult;
    if( init != aText )
        aResult += " > " + init;
    QStringList aTranslation = myModel->Translation(init);
    if( !aTranslation.isEmpty() )
        aResult += " > " + aTranslation.join(", ");
    return aResult;
}

void TextModel::setAsKnownCpp(QString theWord)
{
    //qDebug() << theWord << theIndex;

    myNbUnknown = 0;
    QString aWord = theWord.toLower();
    for(int i=0, n=myItems.size(); i<n; i++)
    {
        if(myItems[i].Text.toLower()==aWord)
            myItems[i].IsKnown = true;
        if(myItems[i].IsWord && !myItems[i].IsKnown)
        {
            //qDebug() << myItems[i].Text;
            myNbUnknown++;
        }
    }

    emit nbUnknownChanged(myNbUnknown);
}

void TextModel::setTrim(bool isTrim)
{
    myItems.setTrim(isTrim);
    emit trimChanged(isTrim);
}

void TextModel::setLimit(int theLimit)
{
    myItems.setLimit(theLimit);
    emit limitChanged(theLimit);
}

bool TextModel::trim() const
{
    return myItems.trim();
}

int TextModel::limit() const
{
    return myItems.limit();
}

QString TextModel::language() const
{
    return myLanguage;
}

void TextModel::setLanguage(QString theLanguage)
{
    qDebug() << "TextModel::setLanguage" << theLanguage;

    if (myLanguage == theLanguage)
        return;

    myLanguage = theLanguage;
    QString anExtLanguage = Helper::extLanguage(myLanguage);
    setProgressPath("../lang/progress/" + anExtLanguage);
    setTextPath("../lang/texts/" + anExtLanguage);
    emit languageChanged(myLanguage);
}

void TextModel::setProgressPath(QString theProgressPath)
{
    qDebug() << "TextModel::setProgressPath" << theProgressPath;

    if (myProgressPath == theProgressPath)
        return;

    myProgressPath = theProgressPath;
    load();
    emit progressPathChanged(myProgressPath);
}

void TextModel::setTextPath(QString theTextPath)
{
    qDebug() << "TextModel::setTextPath" << theTextPath;

    if (myTextPath == theTextPath)
        return;

    myTextPath = theTextPath;
    load();
    emit textPathChanged(myTextPath);
}

QString TextModel::progressPath() const
{
    return myProgressPath;
}

QString TextModel::textPath() const
{
    return myTextPath;
}

int TextModel::nbUnknown() const
{
    return myNbUnknown;
}
