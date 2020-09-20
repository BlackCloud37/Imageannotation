#include "magnifyingglass.h"
#include <QVBoxLayout>
#include <QSlider>
#include <QLabel>
MagnifyingGlass::MagnifyingGlass(QWidget *parent) : QDockWidget(parent)
{
	setWindowTitle("Magnifying");

	setFeatures(QDockWidget::DockWidgetClosable);
	setFeatures(QDockWidget::DockWidgetMovable);
	setFeatures(QDockWidget::DockWidgetFloatable);

	resize(400,400);
	QWidget* dockContent = new QWidget(this);

	QSlider* slider = new QSlider(Qt::Horizontal);
	slider->setParent(dockContent);
	slider->setRange(2, 6);
	connect(slider, &QSlider::valueChanged,
			this, &MagnifyingGlass::ratioChanged);



	view = new QGraphicsView(dockContent);
	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->scale(ratio, ratio);

	QLabel* label = new QLabel(dockContent);
	label->setFont(QFont("Console",10,1));
	label->setMargin(0);
	connect(slider, &QSlider::valueChanged,[=](int value) {
		label->setText(QString::number(value));
	});

	QWidget *sliderWidget = new QWidget(dockContent);
	QHBoxLayout* sliderLayout = new QHBoxLayout();
	sliderLayout->addWidget(slider);
	sliderLayout->addWidget(label);
	sliderLayout->setMargin(0);
	sliderLayout->setSpacing(0);
	sliderWidget->setLayout(sliderLayout);


	QVBoxLayout* layout = new QVBoxLayout(dockContent);
	layout->addWidget(sliderWidget);
	layout->addWidget(view);
	dockContent->setLayout(layout);
	setWidget(dockContent);


}





void MagnifyingGlass::setPaintScene(PaintScene* s)
{
	if (s){
		scene = s;
		view->setScene(scene);
		view->setSceneRect(scene->sceneRect());
	}
}





bool MagnifyingGlass::isShowing()
{
	return showing;
}

void MagnifyingGlass::showEvent(QShowEvent* e)
{
	showing = true;
}

void MagnifyingGlass::closeEvent(QCloseEvent* e)
{
	showing = false;
}






void MagnifyingGlass::setDisplayPos(QPoint mousePos)
{
	view->centerOn(mousePos);
}




void MagnifyingGlass::ratioChanged(int value)
{
	view->scale(1.0 / double(ratio), 1.0 / double(ratio));
	ratio = value;
	view->scale(ratio, ratio);

}
