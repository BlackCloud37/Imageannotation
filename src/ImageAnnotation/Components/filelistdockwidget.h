#ifndef FILELISTDOCKWIDGET_H
#define FILELISTDOCKWIDGET_H

#include <QWidget>
#include <QDockWidget>
#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QListView>
#include <QEvent>
#include <QKeyEvent>



// 显示文件列表，相应文件选择事件并发送给FileController
class FileListDockWidget : public QDockWidget
{
	Q_OBJECT

	QListWidget* listWidget;
	QLineEdit* lineEdit;
	QWidget* dockContent;
	int currIndex = 0;
public:
	explicit FileListDockWidget(QWidget *parent = nullptr);
	bool eventFilter(QObject* obj, QEvent* event);
signals:
	void itemClicked(const QString&);

public slots:
	void fileAdded(const QString& fileName);
	void fileClosed(const QString& fileName);
	void nextFile();
	void prevFile();
	void openFileFinished();
	void selectItem(const QString& name);
};

#endif // FILELISTDOCKWIDGET_H
