#include "paintscene.h"
#include "Components/mygraphicsview.h"

#define SAFE_DELETE(p) { if (p) { delete (p);     (p) = nullptr; } }

PaintScene::PaintScene(QObject* parent): QGraphicsScene (parent),
	currShapeType(Shape::Figure::Empty), currShape(nullptr), radius(20), isDrawing(false), ifTrackMouse(true) {
	// 初始化参照线
	crossLineX = new QGraphicsLineItem;
	crossLineY = new QGraphicsLineItem;
	squarePenCurse = new QGraphicsRectItem(0,0,0,0);
	circlePenCurse = new QGraphicsEllipseItem(0,0,0,0);

	QPen crossPen;
	crossPen.setColor(QColor(0xe7, 0x4c, 0x3c));
	crossLineX->setPen(crossPen);
	crossLineY->setPen(crossPen);
	squarePenCurse->setPen(crossPen);
	circlePenCurse->setPen(crossPen);
	addItem(crossLineX);
	addItem(crossLineY);


    currPixmap = nullptr;
}






void PaintScene::setCurrentShape(Shape::Figure s)  {
	if(s != currShapeType) {
		currShapeType = s;
	}
}







void PaintScene::setPen(QPen pen, QBrush brush)
{
	currPen = pen;
	currBrush = brush;
}






QBrush& PaintScene::getBrush()
{
	return currBrush;
}







QPen& PaintScene::getPen()
{
	return currPen;
}







void PaintScene::changeCurrImage(QImage image)
{
	QGraphicsView* view = views()[0];//显示用view，views()[1]为放大镜的view

	auto list = items();
	for (auto i: list) {
		if (i) {
			i->setVisible(false);
		}
	}

	if (currPixmap) {
		removeItem(currPixmap);
		SAFE_DELETE(currPixmap);
	}
	QPixmap pix;

	pix = QPixmap::fromImage(image.scaled(view->width(), view->height(), Qt::KeepAspectRatio));
	currPixmap = addPixmap(pix);

	if (currPixmap) {
		setSceneRect(currPixmap->boundingRect());
		currPixmap->setVisible(true);
	}
}












void PaintScene::updateShapes(LabelController* labelController, const QString& imageName)
{
	auto itemList = items();
	for (auto item:itemList) {
		if (item != currPixmap && item != crossLineX && item != crossLineY && item != squarePenCurse && item != circlePenCurse) {
			item->setVisible(false);
		}
	}
	auto shapeList = labelController->getShapesOfImage(imageName);
	for (Shape* s : shapeList) {
		if (s) {
			s->resizeEvent(currPixmap->pixmap().size());
			addItem(s->getItem());		
			s->getItem()->setVisible(true);
			s->getItem()->setZValue(currPixmap->zValue() + 1);
		}
	}
}








void PaintScene::updateShape(Shape* s) {
	if (s) {
		s->setPen(currPen, currBrush);
		s->resizeEvent(currPixmap->pixmap().size());
		addItem(s->getItem());
		s->getItem()->setVisible(true);
		s->getItem()->setZValue(currPixmap->zValue() + 1);
	}

}










void PaintScene::setRadius(int value)
{
	if (value > 0 && value < 100) {
		radius = value;
	}
}








void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {

	// 画图事件忽略右键
	if(!isDrawing && event->button() == Qt::MouseButton::RightButton) {
		QGraphicsScene::mousePressEvent(event);
		return;
	}

	// rect为画笔允许的范围
	QRectF rect;
	if (currShapeType == Shape::CirclePen || currShapeType == Shape::SquarePen) {
		rect = QRect(radius,
					 radius,
					 int(width()) - 2 * radius,
					 int(height()) - 2 * radius);
	}
	else {
		rect = sceneRect();
	}

	// 限制画笔在rect内
	if (!rect.contains(event->scenePos())) {
		QPointF newPos = event->scenePos();
		newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
		newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
		event->setScenePos(newPos);
	}

	// 没有画笔工具时可选中对象，否则不可
	if (currShapeType == Shape::Empty) {
		for (auto i : items()) {
			if (i != currPixmap && i != crossLineX && i != crossLineY && i != circlePenCurse && i != squarePenCurse) {
				i->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges);
			}
		}
	}
	else {
		for (auto i : items()) {
			i->setFlag(QGraphicsItem::ItemIsMovable, false);
			i->setFlag(QGraphicsItem::ItemIsSelectable, false);
		}
	}

	// 画图时显示的笔触
	QPen pen;
	pen.setColor(QColor(0x16, 0xa0, 0x85));
	pen.setWidth(radius < 3? radius : 3);
	setPen(pen, QBrush());



	if (event->scenePos().x() < 0 || event->scenePos().x() > sceneRect().width()
			|| event->scenePos().y() < 0 || event->scenePos().y() > sceneRect().height()) {
		QGraphicsScene::mousePressEvent(event);
		return;
	}


	// 如果当前没有在绘图，则开始新绘图
	if (!isDrawing) {
		isDrawing = true;
		ifTrackMouse = true;
		switch(currShapeType) {
			case Shape::Rect: {
				currShape = new Rect;
				break;
			}
			case Shape::Ellipse: {
				currShape = new Ellipse;
				break;
			}
			case Shape::Curve: {
				currShape = new Curve;
				ifTrackMouse = false;
				break;
			}
			case Shape::Polygon: {
				currShape = new Polygon;
				break;
			}
			case Shape::CirclePen: {
				currShape = new CirclePen;
				currShape->setRadius(radius);
				ifTrackMouse = false;
				break;
			}
			case Shape::SquarePen: {
				currShape = new SquarePen;
				currShape->setRadius(radius);
				ifTrackMouse = false;
				break;
			}
			case Shape::Empty: {
				if (currShape)
					delete currShape;
				currShape = nullptr;
				isDrawing = false;
				break;
			}
		}

		if(currShape) {	
			currShape->setPen(currPen, currBrush);
			addItem(currShape->getItem());
			currShape->mousePress(event);
		}
	}

	// 发送坐标信息
	emit scenePos(QPoint(int(event->scenePos().x()), int(event->scenePos().y())));
	if (currPixmap) {
		// 更新参照线
		crossLineX->setLine(event->scenePos().x(), 0, event->scenePos().x(), currPixmap->pixmap().height());
		crossLineX->setZValue(currPixmap->zValue()+1);
		crossLineY->setLine(0, event->scenePos().y(), currPixmap->pixmap().width(), event->scenePos().y());
		crossLineY->setZValue(currPixmap->zValue()+1);

		if (currShapeType == Shape::SquarePen) {
			addItem(squarePenCurse);
			squarePenCurse->setRect(event->scenePos().x() - radius, event->scenePos().y() - radius, 2 * radius, 2 * radius);
			squarePenCurse->setZValue(currPixmap->zValue()+1);
			squarePenCurse->setVisible(true);
		}
		else {
			squarePenCurse->setVisible(false);
		}

		if (currShapeType == Shape::CirclePen) {
			addItem(circlePenCurse);
			circlePenCurse->setRect(event->scenePos().x() - radius, event->scenePos().y() - radius, 2 * radius, 2 * radius);
			circlePenCurse->setZValue(currPixmap->zValue()+1);
			circlePenCurse->setVisible(true);
		}
		else {
			circlePenCurse->setVisible(false);
		}


        if (currPixmap->contains(event->scenePos()))
		emit sendCurrPosToThreeview(double(event->scenePos().x())/double(currPixmap->pixmap().width()),
									double(event->scenePos().y())/double(currPixmap->pixmap().height()));
	}
	QGraphicsScene::mousePressEvent(event);
}











void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
	// rect为画笔允许的范围
	QRectF rect;
	if (currShapeType == Shape::CirclePen || currShapeType == Shape::SquarePen) {
		rect = QRect(radius,
					 radius,
					 int(width()) - 2 * radius,
					 int(height()) - 2 * radius);
	}
	else {
		rect = sceneRect();
	}

	// 限制画笔在rect内
	if (!rect.contains(event->scenePos())) {
		QPointF newPos = event->scenePos();
		newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
		newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
		event->setScenePos(newPos);
	}


	//绘图事件
	if(currShape && isDrawing) {
		currShape->mouseMove(event);
	}




	// 更新参照线
	if (currPixmap) {
		crossLineX->setLine(event->scenePos().x(), 0, event->scenePos().x(), currPixmap->pixmap().height());
		crossLineX->setZValue(currPixmap->zValue()+1);
		crossLineY->setLine(0, event->scenePos().y(), currPixmap->pixmap().width(), event->scenePos().y());
		crossLineY->setZValue(currPixmap->zValue()+1);
		crossLineX->setVisible(true);
		crossLineY->setVisible(true);

		if (currShapeType == Shape::SquarePen) {
			addItem(squarePenCurse);
			squarePenCurse->setRect(event->scenePos().x() - radius, event->scenePos().y() - radius, 2 * radius, 2 * radius);
			squarePenCurse->setZValue(currPixmap->zValue()+1);
			squarePenCurse->setVisible(true);
		}
		else {
			squarePenCurse->setVisible(false);
		}
		if (currShapeType == Shape::CirclePen) {
			addItem(circlePenCurse);
			circlePenCurse->setRect(event->scenePos().x() - radius, event->scenePos().y() - radius, 2 * radius, 2 * radius);
			circlePenCurse->setZValue(currPixmap->zValue()+1);
			circlePenCurse->setVisible(true);
		}
		else {
			circlePenCurse->setVisible(false);
		}
	}


	// 发送当前鼠标位置
	emit scenePos(QPoint(int(event->scenePos().x()), int(event->scenePos().y())));

	QGraphicsScene::mouseMoveEvent(event);
}







void PaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
	// rect为画笔允许的范围
	QRectF rect;
	if (currShapeType == Shape::CirclePen || currShapeType == Shape::SquarePen) {
		rect = QRect(radius,
					 radius,
					 int(width()) - 2 * radius,
					 int(height()) - 2 * radius);
	}
	else {
		rect = sceneRect();
	}

	// 限制画笔在rect内
	if (!rect.contains(event->scenePos())) {
		QPointF newPos = event->scenePos();
		newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
		newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
		event->setScenePos(newPos);
	}


	if (!currShape) {
		isDrawing = false;
	}

	if (isDrawing) {
		if (currShape->quitDrawing(event) || event->button() == Qt::MouseButton::RightButton) {
			// 结束本次绘画
			isDrawing = false;
			ifTrackMouse = false;
			currShape->mouseRelease(event);

			emit drawFinished(currShape);
			removeItem(currShape->getItem());
			delete currShape;
			currShape = nullptr;
		}
		else {
			currShape->mouseRelease(event);
		}
	}

	for(auto i : selectedItems()) {
		if(i) {
			emit itemSelected(i);
		}

	}
	QGraphicsScene::mouseReleaseEvent(event);
}








PaintScene::~PaintScene() {
	SAFE_DELETE(currPixmap);
	SAFE_DELETE(crossLineX);
	SAFE_DELETE(crossLineY);
	SAFE_DELETE(circlePenCurse);
	SAFE_DELETE(squarePenCurse);
	for (QGraphicsItem* i : items())
		removeItem(i);
}








