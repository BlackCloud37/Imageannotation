#include "labelcontroller.h"
#define SAFE_DELETE(p) { if (p) { delete (p);     (p) = nullptr; } }
LabelController::LabelController(QObject* parent) : QObject (parent)
{

}










LabelController::~LabelController()
{
	for (auto labelList: m_typeToLabel) {
		for (Label*& label: labelList) {
			SAFE_DELETE(label);
		}
	}
}









bool LabelController::createType(const QString& type)
{
	// 不存在此type
	if (!m_typeToCount.contains(type)) {

		m_typeToCount[type] = 0;

		QColor color = QColor(rand()%256, rand()%256, rand()%64);
		m_typeToColor[type] = color;

		m_typeToLabel[type] = QList<Label*>();
		emit typeCreated(type, color);
		return true;
	}
	else {
	// 已经存在，不覆盖创建
		qDebug() << "LabelController::createType::type exists";
		return false;
	}
}










Label* LabelController::createLabel(const QString& type, Area* area) {
	if (!m_typeToCount.contains(type)) {
		createType(type);
	}
	m_typeToCount[type] += 1;
	int id = m_typeToCount[type];
	Label* label = new Label(id, type, m_typeToColor[type], area);

	m_typeToLabel[type].append(label);
	emit labelCreated(type, id);
	return label;
}








bool LabelController::addLabel(Label* label)
{

	if (!label)
		return false;
	QString type = label->getType();
	int id = label->getId();

	if (!m_typeToCount.contains(type)) {
		m_typeToLabel[type] = QList<Label*>();
		m_typeToColor[type] = label->getColor();
		m_typeToCount[type] = id > m_typeToCount[type] ? id : m_typeToCount[type];
		m_typeToLabel[type].append(label);
		emit typeCreated(type, label->getColor());
	}
	else {
		m_typeToCount[type] = id > m_typeToCount[type] ? id : m_typeToCount[type];
		m_typeToLabel[type].append(label);
	}

	emit labelCreated(type, id);
	return true;
}
















bool LabelController::deleteLabel(const QString& type, int id)
{
	for (QList<Label*>& labelList: m_typeToLabel) {
		for (Label*& label: labelList) {
			if (label->getType() == type && label->getId() == id) {
				labelList.removeOne(label);
				SAFE_DELETE(label);
				emit labelDeleted(type, id);
			}
		}
	}
	return true;
}














Label* LabelController::getLabel(const QString& type, int id)
{
	for (QList<Label*>& labelList: m_typeToLabel) {
		for (Label*& label: labelList) {
			if (label->getType() == type && label->getId() == id) {
				return label;
			}
		}
	}
	return nullptr;
}













QList<Label*> LabelController::getLabelsOfImage(const QString& imageName)
{
	QList<Label*> list;
	for (QList<Label*>& labelList: m_typeToLabel) {
		for (Label*& label: labelList) {
			if (label->getArea()->getAllImages().contains(imageName)) {
				list.append(label);
			}
		}
	}
	return list;
}










QList<Shape*> LabelController::getShapesOfImage(const QString& imageName)
{
	QList<Shape*> list;
	auto label_list = getLabelsOfImage(imageName);
	for (Label* label: label_list) {
		if (label) {
			const Area* area = label->getArea();
			if (area){
				Shape* shape = area->getShape(imageName);
				QColor color = label->getColor();
				color.setAlpha(95);
				QBrush brush(color);
				QPen pen(Qt::PenStyle::DashDotLine);
				pen.setWidth(4);
				pen.setColor(label->getColor());
				pen.setBrush(brush);
				shape->setPen(pen, brush);
				list.append(shape);
			}
			else {
				qDebug() << "Label::Controller::getShapesOfImage::Null!";
			}
		}
		else {
			qDebug() << "Label::Controller::getShapesOfImage::Null!";
		}

	}
	return list;
}









Label* LabelController::findParentLabelOfItem(QGraphicsItem* item) {
	for (QList<Label*>& labelList: m_typeToLabel) {
		for (Label*& label: labelList) {
			auto imageList = label->getArea()->getAllImages();
			for (QString image: imageList) {
				if (label->getArea()->getShape(image)->getItem() == item) {
					return label;
				}
			}
		}
	}
	return nullptr;
}








void LabelController::deleteItem(QGraphicsItem* item)
{
	auto label = findParentLabelOfItem(item);
	QString type = label->getType();
	int id = label->getId();
	deleteLabel(type, id);
}








QDomElement LabelController::getElement(QDomDocument& doc)
{
	QDomElement labelControllerElem = doc.createElement("LabelController");

	for (auto type: m_typeToCount.keys()) {
		QDomElement typeElem = doc.createElement("Type");
		typeElem.setAttribute("Type", type);
		typeElem.setAttribute("IdCount", m_typeToCount[type]);

		QDomElement colorElem = doc.createElement("Color");

		colorElem.setAttribute("R", m_typeToColor[type].red());
		colorElem.setAttribute("G", m_typeToColor[type].green());
		colorElem.setAttribute("B", m_typeToColor[type].blue());
		typeElem.appendChild(colorElem);


		for (Label* label: m_typeToLabel[type]) {
			if (label)
				typeElem.appendChild(label->getElement(doc));
		}
		labelControllerElem.appendChild(typeElem);
	}
	return labelControllerElem;
}







QDomElement LabelController::getElementOfImage(QDomDocument& doc, QString imageName)
{
	QDomElement labelControllerElem = doc.createElement("LabelController");

	for (auto type: m_typeToCount.keys()) {
		QDomElement typeElem = doc.createElement("Type");
		typeElem.setAttribute("Type", type);
		typeElem.setAttribute("IdCount", m_typeToCount[type]);

		QDomElement colorElem = doc.createElement("Color");

		colorElem.setAttribute("R", m_typeToColor[type].red());
		colorElem.setAttribute("G", m_typeToColor[type].green());
		colorElem.setAttribute("B", m_typeToColor[type].blue());
		typeElem.appendChild(colorElem);


		for (Label* label: getLabelsOfImage(imageName)) {
			if (label)
				if (label->getType() == type)
					typeElem.appendChild(label->getElement(doc));
		}
		labelControllerElem.appendChild(typeElem);
	}
	return labelControllerElem;
}








LabelController* LabelController::createFromElement(QDomElement elem)
{
	if (elem.isNull())
		return nullptr;

	elem = elem.cloneNode(true).toElement();
	qDebug() << elem.tagName();
	for (int i = 0; i < elem.childNodes().count(); i++ ) {
		auto typeElem = elem.childNodes().at(i).toElement();
		qDebug() << typeElem.tagName();
		QString type = typeElem.attribute("Type", "");

		int idCount = typeElem.attribute("IdCount", "0").toInt();

		QColor color(typeElem.firstChildElement("Color").attribute("R", "0").toInt(),
					 typeElem.firstChildElement("Color").attribute("G", "0").toInt(),
					 typeElem.firstChildElement("Color").attribute("B", "0").toInt());

		if (!m_typeToCount.contains(type)) {
			m_typeToLabel[type] = QList<Label*>();
			m_typeToCount[type] = idCount > m_typeToCount[type] ? idCount : m_typeToCount[type];
			m_typeToColor[type] = color;
			emit typeCreated(type, color);
		}
		m_typeToCount[type] = idCount > m_typeToCount[type] ? idCount : m_typeToCount[type];

		for (int j = 0; j < typeElem.childNodes().count(); j++) {
			auto labelElem = typeElem.childNodes().at(j).toElement();
			qDebug() << labelElem.tagName();
			if (labelElem.tagName() == "Label") {
				Label* label = new Label;
				label->createFromElement(labelElem);
				addLabel(label);
			}
		}
	}
	return this;
}
