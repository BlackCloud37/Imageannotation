#ifndef RECT_H
#define RECT_H

#include "shape.h"
#include <QGraphicsRectItem>
#include "Components/mygraphicsitems.h"
class Rect : public Shape
{
public:
	const Shape::Figure m_type = Shape::Figure::Rect;
	MyGraphicsRectItem* rectItem;

public:
	Rect() {
		rectItem = new MyGraphicsRectItem();
	}

	Rect(const Rect& other) {
		rectItem = new MyGraphicsRectItem(other.rectItem->rect());
	}

	~Rect() {
		if (rectItem)
			delete  rectItem;
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

#endif // RECT_H
