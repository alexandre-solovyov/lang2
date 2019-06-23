#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSslSocket>
#include "textmodel.h"
#include "helper.h"

int main(int argc, char *argv[])
{
    qDebug() << "SSL info: " << QSslSocket::supportsSsl() << QSslSocket::sslLibraryBuildVersionString() << QSslSocket::sslLibraryVersionString();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<TextModel>("com.alex.lang", 1, 0, "TextModel");
    qmlRegisterType<Helper>("com.alex.lang", 1, 0, "Helper");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
