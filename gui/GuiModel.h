
#ifndef GUI_MODEL_H
#define GUI_MODEL_H

#include <model/model.h>
#include <QObject>
#include <QStringList>

class GuiModel : public QObject, public Model
{
    Q_OBJECT

public:
    GuiModel();
    virtual ~GuiModel();

    void Load( const QString& );

    Q_INVOKABLE QStringList randomExercise();

    Q_INVOKABLE QString answer() const;
    Q_INVOKABLE bool checkAnswer( const QString& );

private:
    QList<Exercise> myExercises;
    int             myIndex;
};

#endif // GUI_MODEL_H
