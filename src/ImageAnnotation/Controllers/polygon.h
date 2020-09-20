#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"
#include <QGraphicsPolygonItem>
#include "Components/mygraphicsitems.h"
class Polygon : public Shape
{
public:
	const Shape::Figure m_type = Shape::Figure::Polygon;
	MyGraphicsPolygonItem *polygonItem;

	int last_x, last_y;
	QPolygon m_polygon, tmp_polygon;
public:
	Polygon() {
		polygonItem = new MyGraphicsPolygonItem();
	}
	Polygon(const Polygon& other) {
		polygonItem = new MyGraphicsPolygonItem(other.polygonItem->polygon());

	}
	~Polygon() {
		if (polygonItem)
			delete polygonItem;
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

#endif // POLYGON_H
