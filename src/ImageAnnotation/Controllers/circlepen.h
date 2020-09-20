#ifndef CIRCLEPEN_H
#define CIRCLEPEN_H

#include "shape.h"
#include <cmath>
#include <QPoint>
#include <QList>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QGraphicsEllipseItem>
#include "Components/mygraphicsitems.h"


class CirclePen : public Shape
{
	const Shape::Figure m_type = Shape::Figure::CirclePen;
	MyGraphicsPathItem* pathItem;
	QPainterPath m_path;
	int m_radius;
public:
	CirclePen() {
		pathItem = new MyGraphicsPathItem();
	}

	CirclePen(const CirclePen& other) {
		pathItem = new MyGraphicsPathItem(other.pathItem->path());
		m_radius = other.m_radius;
	}

	~CirclePen() {
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
	void setRadius(int r);
	virtual Shape* clone();
	virtual QDomElement getElement(QDomDocument& doc);
	virtual Shape* createFromElement(QDomElement elem);
};

#endif // CIRCLEPEN_H
