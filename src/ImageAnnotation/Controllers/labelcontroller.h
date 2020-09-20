#ifndef LABELCONTROLLER_H
#define LABELCONTROLLER_H

#include <QSet>
#include <QMap>
#include <QList>
#include <QDebug>
#include <QColor>
#include <QObject>
#include "label.h"
#include "area.h"
#include "shape.h"



// 管理所有Label的Type
// 管理所有Label
// 负责分发id
// 实现Label与程序界面间的连接

class LabelController : public QObject
{
	Q_OBJECT


	//记录为某Type的Label分发的Id
	QMap<QString, int> m_typeToCount;
	//记录某Type下的所有Label
	QMap<QString, QList<Label*> > m_typeToLabel;
	//记录某Type对应的Color,其中Color由Controller自动生成
	QMap<QString, QColor> m_typeToColor;

	bool createType(const QString& type);
public:
	LabelController(QObject* parent = nullptr);
	~LabelController();


public slots:
	//以Area和Type创建Label
	Label* createLabel(const QString& type, Area* area);

	//添加已有Label
	bool addLabel(Label* label);

	//删除Label
	bool deleteLabel(const QString& type, int id);

	//查找Label
	Label* getLabel(const QString& type, int id);

	//取得某张图片的所有Label
	QList<Label*> getLabelsOfImage(const QString& imageName);

	//取得某张图片的所有Shape
	QList<Shape*> getShapesOfImage(const QString& imageName);

	//取得某个GraphicsItem所属的Label
	Label* findParentLabelOfItem(QGraphicsItem* item);
	//删除某个GraphicsItem（及其对应的Label）
	void deleteItem(QGraphicsItem* item);

	//以此LabelController生成DOM节点，保存所有信息
	QDomElement getElement(QDomDocument& doc);
	//仅生成某张图片对应的DOM节点，保存单张图片的Label信息
	QDomElement getElementOfImage(QDomDocument& doc, QString imageName);
	//从DOM节点恢复信息
	LabelController* createFromElement(QDomElement elem);

signals:
	void labelCreated(const QString&, int);
	void labelDeleted(const QString&, int);
	void typeCreated(const QString&, QColor color);
	void typeDeleted(const QString&);
};

#endif // LABELCONTROLLER_H
