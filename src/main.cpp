#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "../include/backend.hpp"

int main(int argc, char *argv[])
	{
	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;

	Backend backend;
	engine.rootContext()->setContextProperty("backend", &backend);

	const QUrl url(u"qrc:/cardsearcher/main.qml"_qs);
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
		&app, [url](QObject *obj, const QUrl &objUrl) {
			if (!obj && url == objUrl)
				QCoreApplication::exit(-1);
		}, Qt::QueuedConnection);
	engine.load(url);

    return app.exec();
	}
