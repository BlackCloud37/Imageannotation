#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "ui_statusbar.h"
#include <QStatusBar>
class StatusBar : public QStatusBar
{
	Q_OBJECT

public:
	explicit StatusBar(QWidget *parent = nullptr);

public slots:
	void setScenePos(QPoint p);
private:
	Ui::StatusBar ui;
};

#endif // STATUSBAR_H
