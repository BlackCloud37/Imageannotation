#ifndef CURVE_H
#define CURVE_H

#include "shape.h"
#include <QPoint>
#include <QList>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include "Components/mygraphicsitems.h"
class Curve : public Shape
{
public:
	const Shape::Figure m_type = Shape::Figure::Curve;
	MyGraphicsPathItem* pathItem;
	QPainterPath m_path;
	int s_x, s_y;
public:
	Curve() {
		pathItem = new MyGraphicsPathItem();
	}


	Curve(const Curve& other) {
		//m_point_list = other.m_point_list;
		m_path = other.m_path;
		pathItem = new MyGraphicsPathItem(other.pathItem->path());
	}


	~Curve() {
		if (pathItem)
			delete  pathItem;
	}





	virtual void mousePress(QGraphicsSceneMouseEvent * event);
	virtual void mouseMove(QGraphicsSceneMouseEvent * event);
	virtual void mouseRelease(QGraphicsSceneMouseEvent* event);
	virtual bool quitDrawing(QGraphicsSceneMouseEvent* event);
	virtual void resizeEvent(QSize newSize);






	virtual QGraphicsItem* getItem() const;
	virtual QGraphicsItem* copyItem() const;
	virtual Figure getType() const {
		return m_type;
	}
	virtual void setPen(QPen pen, QBrush brush);
	virtual Shape* clone();
	virtual QDomElement getElement(QDomDocument& doc);
	virtual Shape* createFromElement(QDomElement elem);
};

#endif // CURVE_H
