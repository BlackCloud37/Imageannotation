#ifndef AREA_H
#define AREA_H

#include <QGraphicsItem>
#include <QList>
#include <QDir>
#include <QFile>
#include <QMap>
#include <QSharedPointer>

#include "shape.h"
#include "rect.h"
#include "ellipse.h"
#include "curve.h"
#include "polygon.h"
#include "circlepen.h"
#include "squarepen.h"
class Label;

// 用于描述一个Label所占的区域
// 2D Label的一个area对应"某张图片"上的"某个形状"
// 3D Label的一个area对应"多张图片"上的"多个形状"，且每张有且只有一个形状
// 需要快速查询到某张图片上的形状，故采用Map，图片名作为图片的唯一标识


class Area
{
	//储存Image-Shape信息
	QMap<QString, Shape*> m_imageShapeMap;
	//记录其所属Label
	Label* m_label;

public:

	Area() {}
	explicit Area(Label* label): m_label(label) { }
	~Area();

	//添加一组Image-Shape
	bool addImageShape(const QString& image, Shape* shape);

	void setLabel(Label* label);

	//取得某Image上的Shape
	Shape* getShape(const QString& image) const;

	const Label* getLabel() const;

	//取得此Area所占的所有图片
	QList<QString> getAllImages() const;

	//获取一个Area的拷贝
	Area* clone() const;

	//获取此Area的DOM节点树，用于保存信息
	QDomElement getElement(QDomDocument& doc);

	//从DOM树恢复Area
	Area* createFromElement(QDomElement elem);
};

#endif // AREA_H
