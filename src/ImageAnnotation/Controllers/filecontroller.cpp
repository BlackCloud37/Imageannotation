#include "filecontroller.h"

FileController::FileController(QObject* parent) : QObject (parent), m_currImageName("") {
	m_image = QMap<QString, QImage>();
}






FileController::~FileController() {
}







bool FileController::addFile(QString& fileName, const QString& filePath, const QImage& image) {
	if (m_image.contains(fileName)) {
		qDebug() << "FileController::addItem::file exists";
		return false;
	}
	else {
		m_image[fileName] = std::move(image);
		m_filePath[fileName] = std::move(filePath);
		m_imageList.append(QPair<QString, QImage>(fileName, image));
		emit fileAdded(fileName);
		return true;
	}
}








bool FileController::removeFile(QString& fileName) {

	if ( !m_image.contains(fileName)) {
		qDebug() << "FileController::removeItem::file doesn't exist";
		return false;
	}
	else {
		m_image.remove(fileName);
		m_filePath.remove(fileName);
		for (int i = 0; i < m_imageList.count(); i++) {
			if (m_imageList[i].first == fileName){
				m_imageList.removeAt(i);
				break;
			}
		}
		emit fileRemoved(fileName);
		if (m_image.count() == 0) {
			emit currImageChanged(QString::Null());
		}
		return true;
	}
}








void FileController::openFile(LabelController* labelController)
{
	QStringList pathes = QFileDialog::getOpenFileNames(nullptr,
													   tr("Open File"),
													   ".",
													   tr("Image Files(*.jpg *.png *.gif *.bmp *.jpeg)"));
	bool addedSucceeded = false;
	for (auto path : pathes) {
		if(!path.isEmpty()) {
			QImageReader reader(path);
			QString fileName = QFileInfo(path).fileName();
			reader.setDecideFormatFromContent(true);
			if(reader.canRead()) {
				QImage image;
				if(reader.read(&image)) {
					addFile(fileName, path, image);
					//auto import xml
					QStringList xmlFile = findFiles(QFileInfo(path).path(), QStringList() << fileName + ".xml");
					if (xmlFile.count() == 1) {
							QFile xml(xmlFile[0]);
							if (!xml.open(QFile::ReadOnly))
								return;
							QDomDocument doc;
							if(!doc.setContent(&xml))
							{
								xml.close();
								return;
							}
							xml.close();
							QDomElement root = doc.documentElement();
							labelController->createFromElement(root);
					}
					else if (xmlFile.count() > 1){
						QMessageBox::warning(nullptr, tr("Warning"),
											 "Too many xml files found!(" + fileName +")");
					}
					addedSucceeded = true;
				}
				else {
					qDebug() << "open is failed...." << reader.errorString();
				}
			}
			else {
				qDebug() << "can not read...." << reader.errorString();
			}
		} else {
			QMessageBox::warning(nullptr, tr("Warning"),
								 tr("You did not select any file."));
		}
	}
	if (addedSucceeded) {
		emit updateFiles();
	}
}








void FileController::openDir(LabelController* labelController)
{
	QString path = QFileDialog::getExistingDirectory(nullptr, tr("Open Dir"), ".");
	bool addedSucceeded = false;
	if (!path.isEmpty()) {
		QDir dir(path);
		auto stringFilter = QStringList() << "*.jpg" << "*.png" << "*.gif" << ".bmp" << ".jpeg";
		auto fileNameList = dir.entryList(stringFilter, QDir::Filter::Files, QDir::SortFlag::Name);
		QImageReader reader;
		for (QString fileName : fileNameList) {
			reader.setFileName(path + "/" + fileName);
			reader.setDecideFormatFromContent(true);

			if(reader.canRead()) {
				QImage image;
				if(reader.read(&image)) {
					addFile(fileName, path + "/" + fileName, image);
					addedSucceeded = true;
				}
				else {
					qDebug() << "open is failed...." << reader.errorString();
				}
			}
			else {
				qDebug() << "can not read...." << reader.errorString();
			}
		}
		//auto import xml
		QStringList xmlFile = findFiles(path, QStringList() << "*.xml");
		if (xmlFile.count() == 1) {
				QFile xml(xmlFile[0]);
				if (!xml.open(QFile::ReadOnly))
					return;
				QDomDocument doc;
				if(!doc.setContent(&xml))
				{
					xml.close();
					return;
				}
				xml.close();
				QDomElement root = doc.documentElement();
				labelController->createFromElement(root);
		}
	}
	if (addedSucceeded) {
		emit updateFiles();
	}
}








void FileController::saveFile(LabelController* labelController)
{
	if (m_currImageName == "")
		return;
	if (m_imageList.empty())
		return;

	QString currImageDir = QFileInfo(getCurrImagePath()).path();

	QStringList xmlFile = findFiles(currImageDir, QStringList() << getCurrImageName() + ".xml");

	if (xmlFile.count() == 1) {
		//已经存在，则覆盖
		QFile file(xmlFile[0]);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
			return;
		}
		QDomDocument doc;
		QDomProcessingInstruction instruction;
		instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
		doc.appendChild(instruction);

		doc.appendChild(labelController->getElementOfImage(doc, getCurrImageName()));

		QTextStream out_stream(&file);
		doc.save(out_stream, 4);
		file.close();
	}
	else {
		//未存在，则新建

		QString path = QFileDialog::getSaveFileName(nullptr,
															tr("Open File"),
                                                            getCurrImagePath(),
															tr("XML Files(*.xml)"));

		QFile file(path);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
			return;
		}
		QDomDocument doc;
		QDomProcessingInstruction instruction;
		instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
		doc.appendChild(instruction);

		doc.appendChild(labelController->getElementOfImage(doc, getCurrImageName()));

		QTextStream out_stream(&file);
		doc.save(out_stream, 4);
		file.close();
	}
}










void FileController::saveAsFile(LabelController* labelController)
{
	QString path = QFileDialog::getSaveFileName(nullptr,
														tr("Open File"),
														".",
														tr("XML Files(*.xml)"));
	if (!path.isEmpty()) {
		QFile file(path);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
			QMessageBox::warning(nullptr, tr("Write File"),
									   tr("Cannot open file:\n%1").arg(path));
			return;
		}

		QDomDocument doc;
		//XML Head
		QDomProcessingInstruction instruction;
		instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
		doc.appendChild(instruction);

		doc.appendChild(labelController->getElement(doc));
		QTextStream out_stream(&file);
		doc.save(out_stream, 4);
		file.close();
	}
	else {
		QMessageBox::warning(nullptr, tr("Path"),
									 tr("You did not select any file."));
	}
}








void FileController::importFromFile(LabelController* labelController)
{
	QString path = QFileDialog::getOpenFileName(nullptr, tr("Open File"), ".",
												tr("XML Files(*.xml)"));
	if(!path.isEmpty()) {
		QFile file(path);
		if (!file.open(QFile::ReadOnly))
			return;
		QDomDocument doc;
		if(!doc.setContent(&file))
		{
			file.close();
			return;
		}
		file.close();
		QDomElement root = doc.documentElement();
		labelController->createFromElement(root);
	} else {
		QMessageBox::warning(nullptr, tr("Path"),
							 tr("You did not select any file."));
	}

}






void FileController::openFileByPath(const QString& path)
{
	bool addedSucceeded = false;

	if(!path.isEmpty()) {
		QImageReader reader(path);
		QString fileName = QFileInfo(path).fileName();
		reader.setDecideFormatFromContent(true);
		if(reader.canRead()) {
			QImage image;
			if(reader.read(&image)) {
				addFile(fileName, path, image);
				addedSucceeded = true;
			}
			else {
				qDebug() << "open is failed...." << reader.errorString();
			}
		}
		else {
			qDebug() << "can not read...." << reader.errorString();
		}
	}
	if (addedSucceeded) {
		emit updateFiles();
	}
}






QStringList FileController::findFiles(const QString& startDir, QStringList filters)
{
	QStringList fileNames;
	QDir dir(startDir);

	//current dir
	for (QString file : dir.entryList(filters, QDir::Files) )
		fileNames += startDir + '/' + file;

	//sub dirs
	for (QString subdir : dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot) )
		fileNames += findFiles(startDir + '/' + subdir, filters);

	return fileNames;
}














const QImage FileController::getImage(const QString& fileName) const {
	if ( !m_image.contains(fileName)) {
		qDebug() << "FileController::getImage::file doesn't exist";
		return QImage();
	}
	else {
		qDebug() << "FileController::getImage::found image";
		return m_image.value(fileName);
	}
}






QList<QImage> FileController::getImages() const
{
	QList<QImage> list;
	for (auto p : m_imageList) {
		list.append(p.second);
	}
	return list;
}





int FileController::getIndexOfImage(QString imageName) const
{
	for (int i = 0; i < m_imageList.count(); i++) {
		if (m_imageList[i].first == imageName) {
			return i;
		}
	}
	return -1;
}










QString FileController::getFilePath(const QString& fileName) const {
	if ( !m_filePath.contains(fileName)) {
		qDebug() << "FileController::getFilePath::file doesn't exist";
		return QString();
	}
	else {
		return m_filePath.value(fileName);
	}
}










QString FileController::getCurrImageName() const
{
	return m_currImageName;
}










QString FileController::getCurrImagePath() const
{
	if (m_filePath.contains(m_currImageName)) {
		QString ret = m_filePath.value(m_currImageName);
		qDebug() << ret;
		return ret;
	}
	else {
		qDebug() << "FileController::getCurrImagePath";
		return QString();
	}
}








bool FileController::hasCurrImage()
{
	return (!getCurrImagePath().isEmpty() && !getCurrImagePath().isNull());
}










void FileController::setCurrImageName(const QString& name)
{
	if (m_image.contains(name)) {
		m_currImageName = name;
		emit currImageChanged(name);
	}
	else {
		qDebug() << "FileController::setCurrImageName";
	}
}

