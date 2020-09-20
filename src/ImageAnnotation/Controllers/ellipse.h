#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"
#include <QGraphicsEllipseItem>
#include "Components/mygraphicsitems.h"
class Ellipse : public Shape
{
public:
	const Shape::Figure m_type = Shape::Figure::Ellipse;
	MyGraphicsEllipseItem *ellipseItem;

public:
	Ellipse() {
		ellipseItem = new MyGraphicsEllipseItem();
	}
	Ellipse(const Ellipse& other) {
		ellipseItem = new MyGraphicsEllipseItem(other.ellipseItem->rect());
	}
	~Ellipse() {
		if (ellipseItem)
			delete  ellipseItem;
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

#endif // ELLIPSE_H
