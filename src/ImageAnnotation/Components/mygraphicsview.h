#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QWheelEvent>


// 重写QGraphicsView以支持滚轮事件和缩放
class MyGraphicsView : public QGraphicsView
{
	Q_OBJECT
	double m_scale = 1.0;
public:
	explicit MyGraphicsView(QWidget *parent = nullptr);

protected:
	void resizeEvent(QResizeEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;
signals:
	void viewResized(QResizeEvent*);

public slots:

};

#endif // MYGRAPHICSVIEW_H
