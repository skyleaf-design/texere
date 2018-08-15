#include "TexereWindow.h"

#include <QTextStream>
#include <QDebug>

#include <QWidget>
#include <QQuickWidget>

#include <iostream>


TexereWindow::TexereWindow(QWidget *parent)
	: QMainWindow(parent)
{
	
	setup_root_view();
	this->resize(1024, 800);
	responsive_view->resize(1024, 800);
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
	std::cout << the_width << std::endl;
	responsive_view->resize(the_width, responsive_view->height());
}