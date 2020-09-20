#include "drawfinisheddialog.h"

DrawFinishedDialog::DrawFinishedDialog(QWidget *parent) :
	QDialog(parent)
{
	ui.setupUi(this);
}






void DrawFinishedDialog::setList(const QList<QListWidgetItem*>& list) {
	ui.listWidget->clear();
	for (int i = 0; i < list.count() ; i++) {
		if (list[i])
			ui.listWidget->addItem(list[i]->text());
    }
}

void DrawFinishedDialog::showEvent(QShowEvent *e)
{
    ui.lineEdit->selectAll();
}






void DrawFinishedDialog::on_listWidget_itemClicked(QListWidgetItem *item)
{
	ui.lineEdit->setText(item->text());
}






void DrawFinishedDialog::on_buttonBox_accepted()
{
	auto text = ui.lineEdit->text();
	if (text.isNull() || text.isEmpty()){
		QMessageBox::warning(this, tr("Warn"), tr("No label name inputed!"));
	}
	else {
		emit sendTypeName(text);
	}
}






void DrawFinishedDialog::on_buttonBox_rejected()
{

}
