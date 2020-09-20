#ifndef AREACONTROLLER_H
#define AREACONTROLLER_H
#include <QMap>
#include <QObject>
#include "area.h"


//用于临时管理绘图事件完成后产生的Shape，将其打包到Area以供Label创建使用
class AreaController : public QObject
{
	Q_OBJECT
	Area* m_currArea;

public:
	AreaController(QObject *parent = nullptr);
	~AreaController() {
	}

	// 取走当前的Area并将m_currArea置空
	Area* takeArea();

	// 取得当前的Area在某Image上的Shape
	Shape* getCurrAreaShape(QString imageName) const ;

	bool hasCurrArea() const;
signals:

public slots:
	// 接收Image-Shape
	void receiveImageShape(const QString& image, Shape* shape);
};

#endif // AREACONTROLLER_H
