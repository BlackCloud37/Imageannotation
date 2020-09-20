#include "labeltypedockwidget.h"

LabelTypeDockWidget::LabelTypeDockWidget(QWidget *parent) : QDockWidget(parent)
{
	{
		// This
		setWindowTitle("Label Type");
		setAllowedAreas(Qt::DockWidgetArea::RightDockWidgetArea);
		setFeatures(QDockWidget::NoDockWidgetFeatures);
		setFeatures(QDockWidget::DockWidgetClosable);
		setFeatures(QDockWidget::DockWidgetMovable);
	}


	{
		// ListWidget
		listWidget = new QListWidget(this);
		setWidget(listWidget);
		connect(listWidget, &QListWidget::itemClicked,
				[&](QListWidgetItem* item) {
			emit itemClicked(item->text());
		});
	}
}






QList<QListWidgetItem*> LabelTypeDockWidget::getItemList() const
{
	QList<QListWidgetItem*> list;
	for (int i = 0; i < listWidget->count(); i++) {
		list.append(listWidget->item(i));
	}
	return list;
}






void LabelTypeDockWidget::typeCreated(const QString& type, QColor color)
{
	auto item = new QListWidgetItem(type);
	//设置背景色
	color.setAlpha(80);
	item->setBackgroundColor(color);
	listWidget->addItem(item);
}







void LabelTypeDockWidget::typeDeleted(const QString& type)
{
	auto items = listWidget->findItems(type, Qt::MatchExactly);
	for (auto item: items) {
		listWidget->removeItemWidget(item);
	}
}
