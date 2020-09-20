#include "polygon.h"


void Polygon::mousePress(QGraphicsSceneMouseEvent* event)
{
	auto x = event->scenePos().x();
	auto y = event->scenePos().y();
	last_x = x;
	last_y = y;
	tmp_polygon << QPoint(x, y);
	polygonItem->setPolygon(tmp_polygon);
}








void Polygon::mouseMove(QGraphicsSceneMouseEvent* event)
{
	if (!m_quit){
		auto x = event->scenePos().x();
		auto y = event->scenePos().y();
		tmp_polygon.setPoint(tmp_polygon.size() - 1, x, y);
		polygonItem->setPolygon(tmp_polygon);
	}
}








void Polygon::mouseRelease(QGraphicsSceneMouseEvent* event)
{
	auto x = event->scenePos().x();
	auto y = event->scenePos().y();

	if (m_quit)
		return;

	if (event->button() == Qt::MouseButton::RightButton) {
		x = last_x;
		y = last_y;
		m_polygon << QPoint(x, y);
		m_quit = true;
		polygonItem->setPolygon(m_polygon);
	}

	else {
		if (!m_quit){
			tmp_polygon << QPoint(x, y);
			last_x = x;
			last_y = y;
			m_polygon << QPoint(x, y);
			polygonItem->setPolygon(tmp_polygon);
		}
	}

}












bool Polygon::quitDrawing(QGraphicsSceneMouseEvent* event)
{
	return m_quit;
}








void Polygon::resizeEvent(QSize newSize)
{
	if (!polygonItem)
		return;
	if (m_currSize.width() == 0 || m_currSize.height() == 0) {
		m_currSize = newSize;
	}
	else {
		double ratio = double(newSize.width()) / double(m_currSize.width());
		m_currSize = newSize;
		if (ratio <= 0)
			return;


		polygonItem->setScenePos(polygonItem->scenePos());

		QPolygonF prev = polygonItem->polygon();
		QPolygonF newone;
		for (int i = 0; i < prev.count(); i++) {
			auto point = prev.at(i);
			newone << QPointF(point * ratio);
		}
		polygonItem->setPolygon(newone);
	}
}









QGraphicsItem* Polygon::getItem() const
{
	return polygonItem;
}








QGraphicsItem* Polygon::copyItem() const
{
	//auto ret = new QGraphicsPolygonItem(m_polygon);
	auto ret = new QGraphicsPolygonItem(polygonItem->polygon());
	ret->setPen(polygonItem->pen());
	ret->setBrush(polygonItem->brush());
	return ret;
}









void Polygon::setPen(QPen pen, QBrush brush)
{
	polygonItem->setPen(pen);
	polygonItem->setBrush(brush);
}








Shape* Polygon::clone()
{
	return new Polygon(*this);
}




QDomElement Polygon::getElement(QDomDocument& doc)
{
	QDomElement shapeElem = doc.createElement("Shape");
	shapeElem.setAttribute("Type", getType());
	shapeElem.setAttribute("WidthOfImage", m_currSize.width());
	shapeElem.setAttribute("HeightOfImage", m_currSize.height());
	QDomElement itemElem = doc.createElement("Item");
	auto item = polygonItem->polygon();
	auto pointList = item.toList();

	for (int i = 0; i < pointList.count(); i++) {
		auto point = pointList[i];
		QDomElement pointElem = doc.createElement("Point");
//		pointElem.setTagName("Point");
		pointElem.setAttribute("Index", i);
		pointElem.setAttribute("X", int(point.x()));
		pointElem.setAttribute("Y", int(point.y()));

		itemElem.appendChild(pointElem);
	}

	shapeElem.appendChild(itemElem);

	return shapeElem;
}





Shape* Polygon::createFromElement(QDomElement elem)
{
	if (elem.isNull())
		return nullptr;
	m_currSize = QSize(elem.attribute("WidthOfImage", "0").toInt(), elem.attribute("HeightOfImage", "0").toInt());

	auto itemElem = elem.firstChildElement("Item");
	auto pointNodes = itemElem.childNodes();
	QPolygon polygon;
	for (int i = 0; i < pointNodes.count(); i++) {
		QDomElement pointElem = pointNodes.at(i).toElement();
		polygon << QPoint(pointElem.attribute("X", "0").toInt(), pointElem.attribute("Y", "0").toInt());
	}


	polygonItem->setPolygon(polygon);
	return this;
}

