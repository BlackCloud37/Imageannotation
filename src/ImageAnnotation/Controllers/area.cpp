#include "area.h"







Area::~Area()
{
	for(Shape*& s : m_imageShapeMap) {
		if (s) {
			delete s;
			s = nullptr;
		}

	}
}








bool Area::addImageShape(const QString& image, Shape* shape)
{
	if (!shape)
		return false;

	if (m_imageShapeMap.contains(image)) {
		qDebug() << "Area::addImageShape::image exists";
		//一张图片上有且仅有一个Shape, 以最后一次为准
		if (m_imageShapeMap[image]) {
			delete  m_imageShapeMap[image];
		}
		m_imageShapeMap[image] = shape;
		return true;
	}
	m_imageShapeMap[image] = shape;
	return true;
}








void Area::setLabel(Label* label)
{
	m_label = label;
}









Shape* Area::getShape(const QString& image) const
{
	if (m_imageShapeMap.contains(image))
		return m_imageShapeMap.value(image);
	else {
		qDebug() << "Area::getShape::key does not exist";
		return nullptr;
	}
}








const Label* Area::getLabel() const
{
	if (m_label)
		return m_label;
	else {
		return nullptr;
	}
}








QList<QString> Area::getAllImages() const
{
	if (!m_imageShapeMap.empty())
		return m_imageShapeMap.keys();
	else {
		return QList<QString>();
	}
}




Area* Area::clone() const
{
	Area* area = new Area(m_label);
	for (QString imageName: m_imageShapeMap.keys()) {
		area->addImageShape(imageName, m_imageShapeMap[imageName]->clone());
	}
	return area;
}








QDomElement Area::getElement(QDomDocument& doc)
{
	QDomElement areaElem = doc.createElement("Area");


	for (auto imageName: m_imageShapeMap.keys()) {
		QDomElement imageElem = doc.createElement("ImageShape");

		imageElem.setAttribute("ImageName", imageName);

		QDomElement shapeElem = m_imageShapeMap[imageName]->getElement(doc);

		imageElem.appendChild(shapeElem);

		areaElem.appendChild(imageElem);
	}
	return areaElem;
}






Area* Area::createFromElement(QDomElement elem)
{
	if (elem.isNull())
		return nullptr;

	auto imageNodes = elem.childNodes();
	for (int i = 0; i < imageNodes.count(); i++) {
		auto imageElem = imageNodes.at(i).toElement();
		QString imageName = imageElem.attribute("ImageName", "");

		if (imageName == "")
			continue;

		auto shapeElem = imageElem.firstChildElement("Shape");

		if (shapeElem.isNull())
			continue;

		Shape* shape = nullptr;
		switch (shapeElem.attribute("Type", "0").toInt()) {
		case Shape::Rect: {
			shape = new Rect;
			break;
		}
		case Shape::Ellipse: {
			shape = new Ellipse;
			break;
		}
		case Shape::Curve: {
			shape = new Curve;
			break;
		}
		case Shape::Polygon: {
			shape = new Polygon;
			break;
		}
		case Shape::CirclePen: {
			shape = new CirclePen;
			break;
		}
		case Shape::SquarePen: {
			shape = new SquarePen;
			break;
		}
		case Shape::Empty: {
			continue;
		}
		}
		shape->createFromElement(shapeElem);
		addImageShape(imageName, shape);
	}
	return this;
}
