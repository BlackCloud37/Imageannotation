#include "shape.h"

Shape::Shape()
{
	qDebug() << "shape created";
}

Shape::Shape(const Shape& s): m_type(s.m_type), m_quit(s.m_quit)
{

}


Shape::~Shape() {
	qDebug() << "~shape";
}
