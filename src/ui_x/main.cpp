#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);

  QQmlApplicationEngine engine;
  engine.load(QUrl("qrc:/main.qml"));
  return app.exec();
}
