#include "TexereWindow.h"

#include <QTextStream>
#include <QDebug>

#include <QWidget>
#include <QQuickWidget>


TexereWindow::TexereWindow(QWidget *parent)
	: QMainWindow(parent)
{
	this->resize(1024, 800);
	setup_root_view();
}


void TexereWindow::setup_root_view()
{
	QQuickWidget *view = new QQuickWidget;
	view->setParent(this);
	view->setSource(QUrl("qrc:/main.qml"));
	root_viewx = view->rootObject();
}