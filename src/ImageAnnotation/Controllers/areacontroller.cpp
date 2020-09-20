#include "areacontroller.h"
#include <QtDebug>
AreaController::AreaController(QObject *parent): QObject(parent)  {
	m_currArea = nullptr;
}




Area* AreaController::takeArea()
{
	if (!m_currArea) {
		qDebug() << "AreaController::takeArea::no curr area, cann't take!";
		return nullptr;
	}
	Area* ret = m_currArea;
	m_currArea = nullptr;
	return ret;
}





Shape* AreaController::getCurrAreaShape(QString imageName) const
{
	if (!m_currArea)
		return nullptr;
	return m_currArea->getShape(imageName);
}




bool AreaController::hasCurrArea() const
{
	return m_currArea;
}





void AreaController::receiveImageShape(const QString& image, Shape* shape) {
	if (!m_currArea) {
		m_currArea = new Area();
	}
	m_currArea->addImageShape(image, shape);
}



