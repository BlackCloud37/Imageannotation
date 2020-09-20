#include "graphicsview.h"

GraphicsView::GraphicsView(QWidget* parent): QGraphicsView (parent)
{
	setAlignment(Qt::AlignHCenter | Qt::AlignTop);
	setRenderHint(QPainter::Antialiasing);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}
