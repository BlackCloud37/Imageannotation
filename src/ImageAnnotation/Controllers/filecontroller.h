#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H
#include <QDir>
#include <QtDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QImage>
#include <QList>
#include <QImageReader>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QDomDocument>
#include "labelcontroller.h"


// 在mainwindow与文件组件间通信
// 负责运行时的文件储存
// 负责文件保存及读取的处理工作

class FileController : public QObject
{
	Q_OBJECT

	//文件名-文件路径(包含文件名)的映射
	QMap<QString, QString> m_filePath;
	//文件名-图片的映射
	QMap<QString, QImage> m_image;
	QList<QPair<QString, QImage> > m_imageList;

	//标识当前文件
	QString m_currImageName;





public:
	FileController(QObject* parent = nullptr);
	~FileController();


public slots:
	//添加一个文件
	bool addFile(QString& fileName, const QString& filePath, const QImage& image);
	//关闭一个文件
	bool removeFile(QString& fileName);

	//打开单个/多个文件，并自动导入(图片名.xml)文件
	void openFile(LabelController* labelController);

	//打开文件夹，并自动导入(文件夹名.xml)文件
	void openDir(LabelController* labelController);

	//保存单张图片的Label信息
	void saveFile(LabelController* labelController);

	//保存当前所有图片的Label信息
	void saveAsFile(LabelController* labelController);

	//手动导入Label信息
	void importFromFile(LabelController* labelController);

	//根据路径打开文件
	void openFileByPath(const QString& path);

	//文件搜索
	QStringList findFiles(const QString& startDir, QStringList filters);


	const QImage getImage(const QString& fileName) const;
	QList<QImage> getImages() const;
	int getIndexOfImage(QString imageName) const;
	QString getFilePath(const QString& fileName) const;
	QString getCurrImageName() const;
	QString getCurrImagePath() const;

	bool hasCurrImage();
	void setCurrImageName(const QString& name);

signals:
	void fileAdded(const QString&);
	void fileRemoved(const QString&);
	void updateFiles();
	void currImageChanged(const QString&);
};

#endif // FILECONTROLLER_H
