#ifndef LABELTYPEDOCKWIDGET_H
#define LABELTYPEDOCKWIDGET_H

#include <QWidget>
#include <QDockWidget>
#include <QListWidget>
#include <QGridLayout>
#include <QDebug>
#include <QListView>
#include <QListWidgetItem>



//显示标签Type列表
class LabelTypeDockWidget : public QDockWidget
{
	Q_OBJECT

	QListWidget* listWidget;
public:
	explicit LabelTypeDockWidget(QWidget *parent = nullptr);

	QList<QListWidgetItem*> getItemList() const;
signals:
	void itemClicked(const QString&);

public slots:
	void typeCreated(const QString& type, QColor color);
	void typeDeleted(const QString& type);
};

#endif // LABELTYPEDOCKWIDGET_H
