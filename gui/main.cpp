#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTime>
#include <gui/GuiModel.h>

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qsrand(QTime::currentTime().msecsSinceStartOfDay());
    GuiModel gui_model;
    gui_model.Load("D:/asl/lang/progress/french/fr_noms.lang");//TODO: via properties

    QQmlContext* context = engine.rootContext();
    context->setContextProperty( "gui_model", &gui_model );

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
