
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

private:
    QList<Exercise> myExercises;
};

#endif // GUI_MODEL_H
