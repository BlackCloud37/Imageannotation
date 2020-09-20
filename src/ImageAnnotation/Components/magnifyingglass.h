#ifndef MAGNIFYINGGLASS_H
#define MAGNIFYINGGLASS_H

#include <QWidget>
#include <QDockWidget>
#include <QGraphicsView>
#include "Controllers/paintscene.h"



//放大镜Dock，用一个View显示绘图Scene并可设定倍率
class MagnifyingGlass : public QDockWidget
{
	Q_OBJECT
	QGraphicsView* view;
	PaintScene* scene;
	// 倍率
	uint ratio = 3;
	bool showing = false;
public:
	explicit MagnifyingGlass(QWidget *parent = nullptr);
	void setPaintScene(PaintScene* scene);
	bool isShowing();
protected:
	void showEvent(QShowEvent* e);
	void closeEvent(QCloseEvent* e);
signals:

public slots:
	void setDisplayPos(QPoint mousePos);
	void ratioChanged(int value);
};

#endif // MAGNIFYINGGLASS_H
