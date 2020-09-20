#include "mygraphicsview.h"



#define MAX_SCALE 3
#define SCALE_STEP 0.05


MyGraphicsView::MyGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
	setAlignment(Qt::AlignCenter);
	setRenderHint(QPainter::Antialiasing);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

//告知Shape和PaintScene缩放
void MyGraphicsView::resizeEvent(QResizeEvent* event)
{
	emit viewResized(event);
}


//滚轮缩放
void MyGraphicsView::wheelEvent(QWheelEvent* event)
{
	QPoint delta = event->angleDelta();
	if (delta.y() > 0) {
		scale(1 / m_scale, 1 / m_scale);
		m_scale + SCALE_STEP >= MAX_SCALE ? m_scale = MAX_SCALE : m_scale += SCALE_STEP;
		scale(m_scale, m_scale);
	}
	else {
		scale(1 / m_scale, 1 / m_scale);
		m_scale - SCALE_STEP <= 1.0 ? m_scale = 1.0 : m_scale -= SCALE_STEP;
		scale(m_scale, m_scale);
	}
}

