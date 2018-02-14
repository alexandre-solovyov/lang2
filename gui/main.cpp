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

    QMap<QString,QString> arguments;
    for( int i=1; i<argc; i++ )
    {
        QString a = argv[i];
        QStringList parts = a.split("=", QString::SkipEmptyParts);
        QString p1 = parts.size()>0 ? parts[0] : "";
        QString p2 = parts.size()>1 ? parts[1] : "";
        arguments[p1] = p2;
    }

    QString aFile = arguments["file"];
    if( aFile.isEmpty() )
        aFile = "D:/asl/lang/progress/french/fr_noms.lang";

    qsrand(QTime::currentTime().msecsSinceStartOfDay());
    GuiModel gui_model;
    gui_model.Load(aFile);

    QQmlContext* context = engine.rootContext();
    context->setContextProperty( "gui_model", &gui_model );

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
