#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenuBar>
#include <QMenu>
#include "myactions.h"


class MenuBar : public QMenuBar
{
	Q_OBJECT
public:
	explicit MenuBar(QWidget *parent = nullptr);
signals:
};

#endif // MENUBAR_H
