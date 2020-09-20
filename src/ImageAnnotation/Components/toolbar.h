#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include "Components/myactions.h"
class ToolBar : public QToolBar
{
	Q_OBJECT
public:
	explicit ToolBar( QWidget *parent = nullptr);
signals:
};

#endif // TOOLBAR_H
