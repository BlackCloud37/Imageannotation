#ifndef SQUAREPEN_H
#define SQUAREPEN_H

#include "shape.h"
#include <cmath>
#include <QPoint>
#include <QList>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QGraphicsEllipseItem>
#include "Components/mygraphicsitems.h"
class SquarePen : public Shape
{
	const Shape::Figure m_type = Shape::Figure::SquarePen;
	MyGraphicsPathItem* pathItem;
	QPainterPath m_path;
	int m_radius;
public:
	SquarePen() {
		pathItem = new MyGraphicsPathItem();
	}

	SquarePen(const SquarePen& other) {
		pathItem = new MyGraphicsPathItem(other.pathItem->path());
		m_radius = other.m_radius;
	}

	~SquarePen() {
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
#endif // SQUAREPEN_H
