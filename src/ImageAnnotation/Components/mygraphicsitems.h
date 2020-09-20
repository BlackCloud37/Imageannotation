#ifndef MYGRAPHICSITEMS_H
#define MYGRAPHICSITEMS_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsPathItem>
#include <QGraphicsScene>

//重写一系列GraphicsItem，以支持自定义的坐标设定和拖动范围限制

class MyGraphicsRectItem : public QGraphicsRectItem
{
public:
	explicit MyGraphicsRectItem(QGraphicsItem* parent = nullptr);
	using QGraphicsRectItem::QGraphicsRectItem;
	void setScenePos(QPointF pos);
protected:
	//限定拖动范围
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

class MyGraphicsEllipseItem : public QGraphicsEllipseItem
{
public:
	explicit MyGraphicsEllipseItem(QGraphicsItem* parent = nullptr);
	using QGraphicsEllipseItem::QGraphicsEllipseItem;
	void setScenePos(QPointF pos);
protected:
	//限定拖动范围
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

class MyGraphicsPolygonItem : public QGraphicsPolygonItem
{
public:
	explicit MyGraphicsPolygonItem(QGraphicsItem* parent = nullptr);
	using QGraphicsPolygonItem::QGraphicsPolygonItem;
	void setScenePos(QPointF pos);
protected:
	//限定拖动范围
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

class MyGraphicsPathItem : public QGraphicsPathItem
{
public:
	explicit MyGraphicsPathItem(QGraphicsItem* parent = nullptr);
	using QGraphicsPathItem::QGraphicsPathItem;
	void setScenePos(QPointF pos);
protected:
	//限定拖动范围
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};
#endif // MYGRAPHICSITEMS_H
