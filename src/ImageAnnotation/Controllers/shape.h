#ifndef SHAPE_H
#define SHAPE_H
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QDebug>
#include <QPen>
#include <QBrush>
#include <QDomDocument>






/*
 * 用来描述二维几何区域的基类
 * 统一提供了绘图所需的接口，供PaintScene绘图，并以虚函数实现多态
 */





class Shape
{

public:
	enum Figure{
		Empty,
		Rect,
		Ellipse,
		Polygon,
		Curve,
		CirclePen,
		SquarePen
	} ;
	Shape();
	virtual ~Shape() = 0;
	Shape(const Shape& s);


public:
	Figure m_type;
	//用以记录绘图是否结束
	bool m_quit = false;
	//记录Shape当前所在图片的Size,在图片缩放时使Shape发生对应的缩放
	QSize m_currSize = QSize(0,0);

	//绘图相关事件
	virtual void mousePress(QGraphicsSceneMouseEvent * event) = 0;
	virtual void mouseMove(QGraphicsSceneMouseEvent * event) = 0;
	virtual void mouseRelease(QGraphicsSceneMouseEvent* event) = 0;
	virtual bool quitDrawing(QGraphicsSceneMouseEvent* event) = 0;

	//resize事件，缩放Shape使其与图片对应
	virtual void resizeEvent(QSize newSize) = 0;


	virtual QGraphicsItem* getItem() const = 0;
	virtual QGraphicsItem* copyItem() const = 0;
	virtual Figure getType() const {
		return m_type;
	}


	virtual void setPen(QPen pen, QBrush brush) = 0;
	virtual void setRadius(int r){}

	//复制Shape
	virtual Shape* clone() = 0;

	//以此Shape创建DOM节点，保存信息
	virtual QDomElement getElement(QDomDocument& doc) = 0;
	//从DOM节点恢复Shape
	virtual Shape* createFromElement(QDomElement elem) = 0;
};

#endif // SHAPE_H
