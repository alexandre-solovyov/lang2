
#ifndef GUI_MODEL_H
#define GUI_MODEL_H

#include <model/LangFile.h>
#include <model/grammar.h>
#include <QObject>
#include <QStringList>

class GuiModel : public QObject, public LangFile
{
    Q_OBJECT

public:
    GuiModel();
    virtual ~GuiModel();

    void Load( const QString& );

    Q_INVOKABLE QStringList randomExercise();

    Q_INVOKABLE QString normalize( const QString& );
    Q_INVOKABLE QString answer() const;
    Q_INVOKABLE bool checkAnswer( const QString& );

private:
    ListOfExercises myExercises;
    Grammar         myGrammar;
    int             myIndex;
};

#endif // GUI_MODEL_H
