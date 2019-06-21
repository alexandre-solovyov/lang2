#include "textmodel.h"
#include <QDebug>
#include <QFile>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <model/Tools.h>

static QRegExp WW("^\\w+");  ///< the regular expression for words
static QRegExp NW("^[\\W\\s]+");  ///< the regular expression for not-words

/**
 * @brief WordInfo::WordInfo
 * Constructor
 * @param theText the text of the word
 * @param theTranslation the translation
 * @param isWord if the text corresponds to a word
 * @param isKnown if the word is known
 */
WordInfo::WordInfo(QString theText, QString theTranslation, bool isWord, bool isKnown)
    : Text(theText), Translation(theTranslation), IsWord(isWord), IsKnown(isKnown)
{
}

/**
 * @brief TextModel::TextModel
 * Constructor
 * @param theParent the parent object
 */
TextModel::TextModel(QObject* theParent)
    : QAbstractListModel(theParent), myModel(new StdModel()), myCurrent(nullptr)
{
    //QString LANG = "en";
    //QString LANGUAGE = "english";
    QString LANG = "de";
    QString LANGUAGE = "german";
#ifdef WIN32
    QString LANG_FOLDER = "d:/lang/";
#else
    QString LANG_FOLDER = "/home/alex/lang/";
#endif


    myProgressDir = LANG_FOLDER + "/progress/" + LANGUAGE;
    myTextDir = LANG_FOLDER + "/texts/" + LANGUAGE;

    myModel->Load( myProgressDir, LANG, true );
    myModel->LoadPrivate( myProgressDir + "/private" );

    Tools::print( "" );
    Tools::print( QString("Nb exercises: %0").arg( myModel->NbExercises() ) );
    // This information should be always printed
    Tools::print( QString("Nb known: %0").arg( myModel->grammar().NbKnown() ) );
    Tools::print( "" );
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
    //qDebug() << "setFileName";
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
    QString aFileName = myTextDir + "/" + myFileName;
    qDebug() << "TextModel::load()" << aFileName;
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
                myItems.append(generate(aPart, isLetter));
        }
        myItems.append(WordInfo("<endline>"));
        myItems.append(WordInfo("<newline>"));
    }
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

void TextModel::setAsKnownCpp(QString theWord, int theIndex)
{
    //qDebug() << theWord << theIndex;
    myItems[theIndex].IsKnown = true;
    //if(myCurrent)
    //    myCurrent->setProperty("isKnown", true);
}
