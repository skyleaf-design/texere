#pragma once

#include <QtWidgets>
#include <QtQuick>

class TexereWindow : public QMainWindow
{
Q_OBJECT

public:
  TexereWindow(QWidget *parent = Q_NULLPTR);

private:
	void setup_root_view();
	QQuickItem *root_viewx;
};
