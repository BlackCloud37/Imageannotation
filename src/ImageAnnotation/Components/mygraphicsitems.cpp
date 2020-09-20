#include "mygraphicsitems.h"

MyGraphicsRectItem::MyGraphicsRectItem(QGraphicsItem* parent)
{

}

void MyGraphicsRectItem::setScenePos(QPointF pos)
{
	setPos(0,0);
	setRect(rect().x() + pos.x(),
			rect().y() + pos.y(),
			rect().width(),
			rect().height());
}



QVariant MyGraphicsRectItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
	if (change == ItemPositionChange && scene()) {
		QPointF newPos = value.toPointF();
		int rectX = int(boundingRect().x());
		int rectY = int(boundingRect().y());
		int rectWidth = int(boundingRect().width());
		int rectHeight = int(boundingRect().height());
		//限定拖动的范围
		QRectF rect(0 - rectX,
					0 - rectY,
					scene()->width() - rectWidth,
					scene()->height() - rectHeight);

		if (!rect.contains(newPos)) {
			newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
			newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
			return newPos;
		}
	}
	return QGraphicsRectItem::itemChange(change, value);
}

MyGraphicsEllipseItem::MyGraphicsEllipseItem(QGraphicsItem* parent)
{

}

void MyGraphicsEllipseItem::setScenePos(QPointF pos)
{

	setPos(0,0);
	setRect(rect().x() + pos.x(),
			rect().y() + pos.y(),
			rect().width(),
			rect().height());
}

QVariant MyGraphicsEllipseItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
	if (change == ItemPositionChange && scene()) {
		QPointF newPos = value.toPointF();
		int rectX = int(boundingRect().x());
		int rectY = int(boundingRect().y());
		int rectWidth = int(boundingRect().width());
		int rectHeight = int(boundingRect().height());
		QRectF rect(0 - rectX,
					0 - rectY,
					scene()->width() - rectWidth,
					scene()->height() - rectHeight);

		if (!rect.contains(newPos)) {
			newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
			newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
			return newPos;
		}
	}
	return QGraphicsEllipseItem::itemChange(change, value);
}

MyGraphicsPolygonItem::MyGraphicsPolygonItem(QGraphicsItem* parent)
{

}

void MyGraphicsPolygonItem::setScenePos(QPointF pos)
{
	setPos(0,0);

	QPolygonF prev;
	for (int i = 0; i < polygon().count(); i++) {
		prev << polygon().at(i) + pos;
	}
	setPolygon(prev);
}

QVariant MyGraphicsPolygonItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
	if (change == ItemPositionChange && scene()) {
		QPointF newPos = value.toPointF();
		int rectX = int(boundingRect().x());
		int rectY = int(boundingRect().y());
		int rectWidth = int(boundingRect().width());
		int rectHeight = int(boundingRect().height());
		QRectF rect(0 - rectX,
					0 - rectY,
					scene()->width() - rectWidth,
					scene()->height() - rectHeight);

		if (!rect.contains(newPos)) {
			newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
			newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
			return newPos;
		}
	}
	return QGraphicsPolygonItem::itemChange(change, value);
}

MyGraphicsPathItem::MyGraphicsPathItem(QGraphicsItem* parent)
{

}

void MyGraphicsPathItem::setScenePos(QPointF pos)
{
	setPos(0,0);

	QPolygonF polygon = path().toFillPolygon();
	QPolygonF newPolygon;
	QPainterPath newPath;
	for (int i = 0; i < polygon.count(); i++) {
		newPolygon << polygon.at(i) + pos;
	}
	newPath.addPolygon(newPolygon);
	setPath(newPath);
}

QVariant MyGraphicsPathItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
	if (change == ItemPositionChange && scene()) {
		QPointF newPos = value.toPointF();
		int rectX = int(boundingRect().x());
		int rectY = int(boundingRect().y());
		int rectWidth = int(boundingRect().width());
		int rectHeight = int(boundingRect().height());

		QRectF rect(0 - rectX,
					0 - rectY,
					scene()->width() - rectWidth,
					scene()->height() - rectHeight);

		if (!rect.contains(newPos)) {
			newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
			newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
			return newPos;
		}
	}
	return QGraphicsPathItem::itemChange(change, value);
}
