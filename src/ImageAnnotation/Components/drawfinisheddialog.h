#ifndef DRAWFINISHEDDIALOG_H
#define DRAWFINISHEDDIALOG_H

#include "ui_drawfinisheddialog.h"
#include <QMessageBox>
#include <QListWidgetItem>
#include <QList>
#include <QtDebug>



// 创建Label时的对话框，用于输入Label的Type
class DrawFinishedDialog : public QDialog
{
	Q_OBJECT
	// 默认创建的Type
	QListWidgetItem* defaultItem = nullptr;
public:
	explicit DrawFinishedDialog(QWidget *parent = nullptr);

	// 在打开对话框时同步对话框的Type列表
	void setList(const QList<QListWidgetItem*>& list);

    void showEvent(QShowEvent* e);
signals:
	// 发送要创建的Type
	void sendTypeName(QString&);

private slots:
	void on_listWidget_itemClicked(QListWidgetItem *item);
	void on_buttonBox_accepted();
	void on_buttonBox_rejected();

private:
	Ui::DrawFinishedDialog ui;
};

#endif // DRAWFINISHEDDIALOG_H
