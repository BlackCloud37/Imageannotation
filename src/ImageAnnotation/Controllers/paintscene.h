#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneEvent>

#include <QWidget>
#include <QtDebug>
#include "shape.h"
#include "rect.h"
#include "ellipse.h"
#include "curve.h"
#include "polygon.h"
#include "circlepen.h"
#include "squarepen.h"
#include "area.h"
#include "labelcontroller.h"
#include "label.h"
#include <QColor>
#include <QPen>
#include <QSharedPointer>
#include <QGraphicsView>
#include <QSet>

/*
 * 捕获鼠标事件
 * 显示图片
 * 创建绘制的对象，并将其发送给Controller
 * 本身只储存绘图相关的信息
 */

class PaintScene : public QGraphicsScene {
	Q_OBJECT

public:
	// 现在绘图的图形种类
	Shape::Figure currShapeType;

	// 正在绘制的图形
	Shape* currShape;

	// 正显示的背景图
	QGraphicsPixmapItem* currPixmap = nullptr;

	// 设定的笔与画刷，由LabelType决定
	QPen currPen;
	QBrush currBrush;
	int radius;


	bool isDrawing;
	bool ifTrackMouse;

	//参照线
	QGraphicsLineItem *crossLineX, *crossLineY;
	QGraphicsRectItem *squarePenCurse;
	QGraphicsEllipseItem *circlePenCurse;


public:
	PaintScene(QObject* parent = nullptr);
	~PaintScene();



public slots:
	//设定画笔种类
	void setCurrentShape(Shape::Figure s);
	//设定画笔样式
	void setPen(QPen pen, QBrush brush);


	QPen& getPen();
	QBrush& getBrush();

	//改变显示的图片
	void changeCurrImage(QImage image);
	//更新显示当前图片的所有Shape
	virtual void updateShapes(LabelController* labelController, const QString& imageName);
	//更新显示某一Shape
	void updateShape(Shape* shape);
	//设定圆形、方画笔粗细
	void setRadius(int value);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);


signals:
	void mouseTrackingOn();
	void mouseTrackingOff();
	void drawFinished(Shape* shape);
	void scenePos(QPoint);
	void sendCurrPosToThreeview(double, double);
	void viewPos(QPoint);
	void itemSelected(QGraphicsItem*);
};




#endif // PAINTSCENE_H
