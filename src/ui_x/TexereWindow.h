#pragma once

#include <QtWidgets>
#include <QtQuick>
#include <QQuickWidget>

class TexereWindow : public QMainWindow
{
		Q_OBJECT

public:
  TexereWindow(QWidget *parent = Q_NULLPTR);

protected:
	void resizeEvent(QResizeEvent * event);

private:
	void setup_root_view();
	void request_list();
	void populate_list(QNetworkReply*);
	QQuickWidget * responsive_view;
};
