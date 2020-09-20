#ifndef LABEL_H
#define LABEL_H
#include <QString>
#include <QList>
#include <QColor>
#include "area.h"

class Label
{
	//标记某Label以与其他Label区分
	int m_id;

	QString m_type;
	QColor m_color;
	Area* m_area;
public:
	Label(){}
	Label(const int id, const QString& type, const QColor color, Area* area);
	~Label();

	int getId() const;
	const QString& getType() const;
	const QColor getColor() const;
	const Area* getArea() const;
	QString getName() const;

	//以此Label创建Dom节点，保存信息
	QDomElement getElement(QDomDocument& doc);
	//以Dom节点恢复Label
	Label* createFromElement(QDomElement elem);

	//复制Label
	Label* clone() const;
};

#endif // LABEL_H
