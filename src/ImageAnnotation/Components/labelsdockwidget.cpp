#include "labelsdockwidget.h"

QString LabelsDockWidget::toName(const QString& type, const int id)
{
	return  type + "_" + QString::number(id);
}







LabelsDockWidget::LabelsDockWidget(QWidget *parent) : QDockWidget(parent) {

	{
		// This
		setWindowTitle("Lables");
		setAllowedAreas(Qt::DockWidgetArea::RightDockWidgetArea);
		setFeatures(QDockWidget::NoDockWidgetFeatures);
		setFeatures(QDockWidget::DockWidgetClosable);
		setFeatures(QDockWidget::DockWidgetMovable);
	}


	{
		// ListWidget
		listWidget = new QListWidget(this);
		connect(listWidget, &QListWidget::itemClicked,
				[&](QListWidgetItem* item) {
			emit itemClicked(item->text());
		});
	}
	{
		pushButton = new QPushButton(this);
		pushButton->setText("Delete Label");
		connect(pushButton, &QPushButton::clicked,
				[&](){
			emit deleteCurrLabel(currLabelName());
		});
	}


	{
		dockContent = new QWidget(this);
		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->addWidget(listWidget, 1);
		layout->addWidget(pushButton, 0);
		layout->setSpacing(0);
		layout->setMargin(0);
		layout->setContentsMargins(0,0,0,0);
		dockContent->setLayout(layout);
		setWidget(dockContent);
	}
}

QString LabelsDockWidget::currLabelName()
{
	if (listWidget->currentItem())
		return listWidget->currentItem()->text();
	else {
		return "";
	}
}












void LabelsDockWidget::labelCreated(const QString& type, const int id)
{
	listWidget->addItem(toName(type, id));
}




void LabelsDockWidget::labelDeleted(const QString& type, const int id)
{
	auto items = listWidget->findItems(toName(type, id), Qt::MatchExactly);
	for (auto item: items) {
		item->setHidden(true);
		listWidget->removeItemWidget(item);

	}
}











void LabelsDockWidget::setLabelList(const QList<Label*> list)
{
	listWidget->clear();
	for (Label* label:list) {
		listWidget->addItem(toName(label->getType(), label->getId()));
	}
}











void LabelsDockWidget::labelSelected(const QString& labelName)
{
	for (int i = 0; i < listWidget->count(); i++) {
		if (listWidget->item(i)->text() == labelName) {
			listWidget->setCurrentRow(i);
			break;
		}
	}
	emit itemClicked(labelName);
}








