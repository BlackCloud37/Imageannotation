#include "squarepen.h"

void SquarePen::mousePress(QGraphicsSceneMouseEvent *event) {
	int x = int(event->scenePos().x());
	int y = int(event->scenePos().y());
	m_path.addRect(QRect(x - m_radius < 0 ? 0 : x - m_radius,
						 y - m_radius < 0 ? 0 : y - m_radius,
						 2 * m_radius,
						 2 * m_radius));
	pathItem->setPath(m_path);
}








void SquarePen::mouseMove(QGraphicsSceneMouseEvent * event) {
	int x = int(event->scenePos().x());
	int y = int(event->scenePos().y());
	QPainterPath p;
	p.addRect(QRect(x - m_radius < 0 ? 0 : x - m_radius,
					y - m_radius < 0 ? 0 : y - m_radius,
					2 * m_radius,
					2 * m_radius));
	m_path = m_path.united(p);
	pathItem->setPath(m_path);
}






void SquarePen::mouseRelease(QGraphicsSceneMouseEvent* event)
{
	int x = int(event->scenePos().x());
	int y = int(event->scenePos().y());
	QPainterPath p;
	p.addRect(QRect(x - m_radius < 0 ? 0 : x - m_radius,
					y - m_radius < 0 ? 0 : y - m_radius,
					2 * m_radius,
					2 * m_radius));
	m_path = m_path.united(p);
	pathItem->setPath(m_path);
}












bool SquarePen::quitDrawing(QGraphicsSceneMouseEvent* event)
{
	return true;
}











void SquarePen::resizeEvent(QSize newSize)
{
	if (!pathItem)
		return;
	if (m_currSize.width() == 0 || m_currSize.height() == 0) {
		m_currSize = newSize;
	}
	else {
		double ratio = double(newSize.width()) / double(m_currSize.width());
		m_currSize = newSize;
		if (ratio <= 0)
			return;
		pathItem->setScenePos(pathItem->scenePos());
		QPolygonF prev = pathItem->path().toFillPolygon();

		QPolygonF newone;
		for (int i = 0; i < prev.count(); i++) {
			auto point = prev.at(i);
			newone << QPointF(point * ratio);
		}


		QPainterPath newPath;
		newPath.addPolygon(newone);
		pathItem->setPath(newPath);
	}
}













QGraphicsItem* SquarePen::getItem() const
{
	return pathItem;
}









QGraphicsItem* SquarePen::copyItem() const
{
	auto ret = new QGraphicsPathItem(pathItem->path());
	ret->setPen(pathItem->pen());
	ret->setBrush(pathItem->brush());
	return ret;
}










void SquarePen::setPen(QPen pen, QBrush brush)
{
	pathItem->setPen(pen);
	pathItem->setBrush(brush);
}








void SquarePen::setRadius(int r)
{
	if (r > 0)
		m_radius = r;
}










Shape* SquarePen::clone()
{
	return new SquarePen(*this);
}







QDomElement SquarePen::getElement(QDomDocument& doc)
{
	QDomElement shapeElem = doc.createElement("Shape");
	shapeElem.setAttribute("Type", getType());
	shapeElem.setAttribute("WidthOfImage", m_currSize.width());
	shapeElem.setAttribute("HeightOfImage", m_currSize.height());
	QDomElement itemElem = doc.createElement("Item");
	auto item = pathItem->path();
	auto pointList = item.toFillPolygon().toList();

	for (int i = 0; i < pointList.count(); i++) {
		auto point = pointList[i];
		QDomElement pointElem = doc.createElement("Point");
		pointElem.setAttribute("Index", i);
		pointElem.setAttribute("X", int(point.x()));
		pointElem.setAttribute("Y", int(point.y()));

		itemElem.appendChild(pointElem);
	}

	shapeElem.appendChild(itemElem);

	return shapeElem;
}






Shape* SquarePen::createFromElement(QDomElement elem)
{
	if (elem.isNull())
		return nullptr;
	m_currSize = QSize(elem.attribute("WidthOfImage", "0").toInt(), elem.attribute("HeightOfImage", "0").toInt());

	auto itemElem = elem.firstChildElement("Item");
	auto pointNodes = itemElem.childNodes();
	QPainterPath path;
	for (int i = 0; i < pointNodes.count(); i++) {
		QDomElement pointElem = pointNodes.at(i).toElement();
		QPoint point = QPoint(pointElem.attribute("X", "0").toInt(), pointElem.attribute("Y", "0").toInt());
		if (i == 0)
			path.moveTo(point);
		path.lineTo(point);
	}
	pathItem->setPath(path);
	return this;
}
