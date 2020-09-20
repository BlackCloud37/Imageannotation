#include "filelistdockwidget.h"

FileListDockWidget::FileListDockWidget(QWidget *parent) : QDockWidget(parent) {

	{
		// This
		setWindowTitle("File List");
		dockContent = new QWidget(this);
		setFeatures(QDockWidget::NoDockWidgetFeatures);
		setFeatures(QDockWidget::DockWidgetClosable);
		setFeatures(QDockWidget::DockWidgetMovable);
		setAllowedAreas(Qt::DockWidgetArea::RightDockWidgetArea);
	}


	{
		lineEdit = new QLineEdit(this);
		lineEdit->setPlaceholderText("Search File");
		lineEdit->installEventFilter(this);
	}

	{
		// ListWidget
		listWidget = new QListWidget(this);
		connect(listWidget, &QListWidget::itemClicked,
				[&](QListWidgetItem* item) {
			emit itemClicked(item->text());
			currIndex = listWidget->row(item);
		});

	}


	{
		// Layout
		QVBoxLayout* vLayout = new QVBoxLayout(this);
		vLayout->addWidget(lineEdit, 0);
		vLayout->addWidget(listWidget, 1);
		vLayout->setContentsMargins(0, 0, 0, 0);
		vLayout->setMargin(0);
		vLayout->setSpacing(0);
		dockContent->setLayout(vLayout);
		setWidget(dockContent);
	}
}




//捕捉lineEdit的回车事件，搜索文件
bool FileListDockWidget::eventFilter(QObject* obj, QEvent* event)
{
	if (obj == lineEdit) {
		if (event->type() == QEvent::KeyPress) {
			QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
			if (keyEvent->key() == Qt::Key::Key_Return) {
				QString fileName = lineEdit->text();
				auto items = listWidget->findItems(fileName, Qt::MatchContains);
				if (items.count()) {
					listWidget->setCurrentItem(items[0]);
					emit itemClicked(items[0]->text());
				}
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return QDockWidget::eventFilter(obj, event);
	}
}




void FileListDockWidget::fileAdded(const QString& fileName)
{

	listWidget->addItem(fileName);

}






void FileListDockWidget::fileClosed(const QString& fileName)
{
	auto items = listWidget->findItems(fileName, Qt::MatchExactly);
	for (auto item: items) {
		if (currIndex == listWidget->row(item)) {
			currIndex = currIndex - 1 <= 0 ? 0 : currIndex - 1;
		}
		listWidget->takeItem(listWidget->row(item));
	}
	if (currIndex >= 0 && currIndex < listWidget->count()) {
		listWidget->setCurrentRow(currIndex);
		emit itemClicked(listWidget->item(currIndex)->text());
	}
}






void FileListDockWidget::nextFile()
{
	if (currIndex >= listWidget->count() - 1) {
		currIndex = listWidget->count() - 1;
	}
	else {
		currIndex++;
		listWidget->setCurrentRow(currIndex);
		emit itemClicked(listWidget->item(currIndex)->text());
	}
}






void FileListDockWidget::prevFile()
{
	if (currIndex <= 0 ) {
		currIndex = 0;
	}
	else {
		currIndex--;
		listWidget->setCurrentRow(currIndex);
		emit itemClicked(listWidget->item(currIndex)->text());
	}
}


void FileListDockWidget::openFileFinished()
{
	currIndex = listWidget->count() - 1;
	listWidget->setCurrentRow(currIndex);
	emit itemClicked(listWidget->item(currIndex)->text());
}

void FileListDockWidget::selectItem(const QString& name)
{
	auto list = listWidget->findItems(name, Qt::MatchExactly);
	if (list.count()) {
		for (auto item : list) {
			listWidget->setCurrentRow(listWidget->row(item));
		}
	}
}







