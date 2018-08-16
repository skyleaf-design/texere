#include "TexereWindow.h"

#include <QTextStream>
#include <QDebug>

#include <QWidget>
#include <QQuickWidget>
#include <QNetworkAccessManager>

#include <QJsonObject>
#include <QJsonDocument>

#include <iostream>


TexereWindow::TexereWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setup_root_view();
	resize(1024, 800);
	responsive_view->resize(1024, 800);
	request_list();
}


void TexereWindow::setup_root_view()
{
	QQuickWidget *view = new QQuickWidget;
	view->setParent(this);
	view->setSource(QUrl("qrc:/main.qml"));
	view->setResizeMode(QQuickWidget::SizeRootObjectToView);
	responsive_view = view;
}

void TexereWindow::resizeEvent(QResizeEvent * event) {
	int the_width = event->size().width();
	responsive_view->resize(the_width, responsive_view->height());
}

void TexereWindow::request_list() {
	QNetworkAccessManager *net = new QNetworkAccessManager(this);
	//connect(manager, SIGNAL(finished(QNetworkReply*)), this, &TexereWindow::populate_list);
	connect(net, &QNetworkAccessManager::finished, this, &TexereWindow::populate_list);

	net->get(QNetworkRequest(QUrl("http://localhost:18080/json")));
}

void TexereWindow::populate_list(QNetworkReply* reply) {
	QByteArray data = reply->readAll();
	QJsonDocument the_json = QJsonDocument::fromJson(data);
  QJsonObject response = the_json.object();
	std::string name = response["name"].toString().toUtf8().constData();
	std::string ship = response["ship"].toString().toUtf8().constData();
	std::string captain = response["captain"].toString().toUtf8().constData();
	std::cout << name << std::endl;
	std::cout << ship << std::endl;
	std::cout << captain << std::endl;
}