#include "rect.h"

void Rect::mousePress(QGraphicsSceneMouseEvent *event) {
	auto x = event->scenePos().x();
	auto y = event->scenePos().y();
	rectItem->setRect(x, y, 0, 0);
}





void Rect::mouseMove(QGraphicsSceneMouseEvent * event) {
	auto width = event->scenePos().x() - rectItem->rect().x();
	auto height = event->scenePos().y() - rectItem->rect().y();
	rectItem->setRect(rectItem->rect().x(), rectItem->rect().y(), width, height);
}





void Rect::mouseRelease(QGraphicsSceneMouseEvent* event)
{
	auto width = event->scenePos().x() - rectItem->rect().x();
	auto height = event->scenePos().y() - rectItem->rect().y();
	rectItem->setRect(rectItem->rect().x(), rectItem->rect().y(), width, height);
	m_quit = true;
}





bool Rect::quitDrawing(QGraphicsSceneMouseEvent* event)
{
	return m_quit;
}






void Rect::resizeEvent(QSize newSize)
{
	if (!rectItem)
		return;
	if (m_currSize.width() == 0 || m_currSize.height() == 0) {
		m_currSize = newSize;
	}
	else {
		double ratio = double(newSize.width()) / double(m_currSize.width());
		m_currSize = newSize;
		if (ratio <= 0)
			return;

		rectItem->setScenePos(rectItem->scenePos());

		QRectF prev = rectItem->rect();
		QRectF newone = QRectF(prev.x() * ratio, prev.y() * ratio, prev.width() * ratio, prev.height() * ratio);
		rectItem->setRect(newone);
	}
}





QGraphicsItem* Rect::getItem() const
{
	return rectItem;
}





QGraphicsItem* Rect::copyItem() const
{
	auto ret = new QGraphicsRectItem(rectItem->rect());
	ret->setPen(rectItem->pen());
	ret->setBrush(rectItem->brush());
	return ret;
}





void Rect::setPen(QPen pen, QBrush brush)
{
	rectItem->setPen(pen);
	rectItem->setBrush(brush);
}





Shape* Rect::clone()
{
	return new Rect(*this);
}



QDomElement Rect::getElement(QDomDocument& doc)
{
	QDomElement shapeElem = doc.createElement("Shape");
	shapeElem.setAttribute("Type", getType());
	shapeElem.setAttribute("WidthOfImage", m_currSize.width());
	shapeElem.setAttribute("HeightOfImage", m_currSize.height());

	QDomElement itemElem = doc.createElement("Item");
	auto item = rectItem->rect();
	itemElem.setAttribute("X", int(item.x()));
	itemElem.setAttribute("Y", int(item.y()));
	itemElem.setAttribute("Width", int(item.width()));
	itemElem.setAttribute("Height", int(item.height()));

	shapeElem.appendChild(itemElem);

	return shapeElem;
}





Shape* Rect::createFromElement(QDomElement elem)
{
	if (elem.isNull())
		return nullptr;
	m_currSize = QSize(elem.attribute("WidthOfImage", "0").toInt(), elem.attribute("HeightOfImage", "0").toInt());

	auto itemElem = elem.firstChildElement("Item");
	QRect rect(itemElem.attribute("X", "0").toInt(),
			   itemElem.attribute("Y", "0").toInt(),
			   itemElem.attribute("Width", "0").toInt(),
			   itemElem.attribute("Height", "0").toInt());
	rectItem->setRect(rect);
	return this;
}

