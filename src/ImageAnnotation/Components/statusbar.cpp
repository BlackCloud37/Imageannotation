#include "statusbar.h"

StatusBar::StatusBar(QWidget *parent) :
	QStatusBar(parent)
{
	ui.setupUi(this);
}

void StatusBar::setScenePos(QPoint p)
{
	ui.scenePosLabel->setText("Scene: (" + QString::number(p.x()) + ", " + QString::number(p.y()) + ")");
}

