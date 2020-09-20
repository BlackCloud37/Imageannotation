#include "label.h"

Label::Label(const int id, const QString& type, const QColor color, Area* area):
	m_id(id), m_type(type), m_color(color), m_area(area) {
	m_area->setLabel(this);
}







Label::~Label() {
	if (m_area)	{
		delete m_area;
	}
}









int Label::getId() const
{
	return m_id;
}








const QString& Label::getType() const
{
	return m_type;
}








const QColor Label::getColor() const
{
	return m_color;
}







const Area* Label::getArea() const
{
	return m_area;
}








QString Label::getName() const
{
	return m_type + "_" + QString::number(m_id);
}








QDomElement Label::getElement(QDomDocument& doc)
{
	QDomElement labelElem = doc.createElement("Label");
	labelElem.setAttribute("Type", m_type);
	labelElem.setAttribute("Id", QString::number(m_id));

	QDomElement colorElem = doc.createElement("Color");
	colorElem.setAttribute("R", QString::number(m_color.red()));
	colorElem.setAttribute("G", QString::number(m_color.green()));
	colorElem.setAttribute("B", QString::number(m_color.blue()));

	labelElem.appendChild(colorElem);

	labelElem.appendChild(m_area->getElement(doc));
	return labelElem;
}




Label* Label::createFromElement(QDomElement elem)
{
	if (elem.isNull())
		return nullptr;
	m_type = elem.attribute("Type", "");
	m_id = elem.attribute("Id", "0").toInt();

	auto colorElem = elem.firstChildElement("Color");
	m_color = QColor(colorElem.attribute("R", "0").toInt(),
					 colorElem.attribute("G", "0").toInt(),
					 colorElem.attribute("B", "0").toInt());
	m_area = new Area;
	m_area->createFromElement(elem.firstChildElement("Area"));

	return this;
}





Label* Label::clone() const
{
	return new Label(m_id, m_type, m_color, m_area->clone());
}
