#include "ellipse.h"
#include <QDebug>
void Ellipse::mousePress(QGraphicsSceneMouseEvent *event) {
	auto x = event->scenePos().x();
	auto y = event->scenePos().y();
	ellipseItem->setRect(x, y, 0, 0);
}






void Ellipse::mouseMove(QGraphicsSceneMouseEvent * event) {
	auto width = event->scenePos().x() - ellipseItem->rect().x();
	auto height = event->scenePos().y() - ellipseItem->rect().y();
	ellipseItem->setRect(ellipseItem->rect().x(), ellipseItem->rect().y(), width, height);
}






void Ellipse::mouseRelease(QGraphicsSceneMouseEvent* event)
{
	auto width = event->scenePos().x() - ellipseItem->rect().x();
	auto height = event->scenePos().y() - ellipseItem->rect().y();
	ellipseItem->setRect(ellipseItem->rect().x(), ellipseItem->rect().y(), width, height);
	m_quit = true;
}









bool Ellipse::quitDrawing(QGraphicsSceneMouseEvent* event)
{
	return m_quit;
}










void Ellipse::resizeEvent(QSize newSize)
{
	if (!ellipseItem)
		return;
	if (m_currSize.width() == 0 || m_currSize.height() == 0) {
		m_currSize = newSize;
	}
	else {
		double ratio = double(newSize.width()) / double(m_currSize.width());
		m_currSize = newSize;
		if (ratio <= 0)
			return;

		ellipseItem->setScenePos(ellipseItem->scenePos());

		QRectF prev = ellipseItem->rect();
		QRectF newone = QRectF(prev.x() * ratio, prev.y() * ratio, prev.width() * ratio, prev.height() * ratio);
		ellipseItem->setRect(newone);
	}
}









QGraphicsItem* Ellipse::getItem() const
{
	return ellipseItem;
}










QGraphicsItem* Ellipse::copyItem() const
{
	auto ret = new QGraphicsEllipseItem(ellipseItem->rect());
	ret->setPen(ellipseItem->pen());
	ret->setBrush(ellipseItem->brush());
	return ret;
}








void Ellipse::setPen(QPen pen, QBrush brush)
{
	ellipseItem->setPen(pen);
	ellipseItem->setBrush(brush);
}









Shape* Ellipse::clone()
{
	return new Ellipse(*this);
}






QDomElement Ellipse::getElement(QDomDocument& doc)
{
	QDomElement shapeElem = doc.createElement("Shape");
//	shapeElem.setTagName("Shape");
	shapeElem.setAttribute("Type", getType());
	shapeElem.setAttribute("WidthOfImage", m_currSize.width());
	shapeElem.setAttribute("HeightOfImage", m_currSize.height());

	QDomElement itemElem = doc.createElement("Item");
	auto item = ellipseItem->rect();
	itemElem.setAttribute("X", int(item.x()));
	itemElem.setAttribute("Y", int(item.y()));
	itemElem.setAttribute("Width", int(item.width()));
	itemElem.setAttribute("Height", int(item.height()));

	shapeElem.appendChild(itemElem);

	return shapeElem;
}





Shape* Ellipse::createFromElement(QDomElement elem)
{
	if (elem.isNull())
		return nullptr;
	m_currSize = QSize(elem.attribute("WidthOfImage", "0").toInt(), elem.attribute("HeightOfImage", "0").toInt());

	auto itemElem = elem.firstChildElement("Item");
	QRect rect(itemElem.attribute("X", "0").toInt(),
			   itemElem.attribute("Y", "0").toInt(),
			   itemElem.attribute("Width", "0").toInt(),
			   itemElem.attribute("Height", "0").toInt());
	ellipseItem->setRect(rect);
	return this;
}
