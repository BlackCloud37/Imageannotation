#include "threeview.h"

#include <QDebug>
#include <algorithm>
#include <iostream>

#include <QPainter>





//从范围内每张图片中选出对应列的像素，生成侧视图及俯视图
void ThreeView::generate() {
	int curr_x = m_curr_point.x();
	int curr_y = m_curr_point.y();


	int leftBorder = m_curr_image_index - m_range_of_images >= 0? m_curr_image_index - m_range_of_images : 0;
	int rightBorder = m_curr_image_index + m_range_of_images < m_all_images.size()? m_curr_image_index + m_range_of_images + 1 : m_all_images.size();

	int leftViewWidth = (rightBorder - leftBorder) * m_duplicate_time;
	int vertViewHeight = (rightBorder - leftBorder) * m_duplicate_time;
	int leftViewHeight = m_all_images[m_curr_image_index].height();
	int vertViewWidth = m_all_images[m_curr_image_index].width();

	QPixmap leftViewPixmap(leftViewWidth, leftViewHeight);
	QPixmap vertViewPixmap(vertViewWidth, vertViewHeight);

	left_view_image = leftViewPixmap.toImage();
	vertical_view_image = vertViewPixmap.toImage();

	QPainter leftPainter(&left_view_image);
	QPainter vertPainter(&vertical_view_image);

	for (int i = leftBorder; i < rightBorder; i ++) {
		int count = i - leftBorder;
		QImage currMainImage = m_all_images[i];

		QRect leftSource(QPoint(curr_x, 0), QPoint(curr_x, currMainImage.height() - 1));
		QRect vertSource(QPoint(0, curr_y), QPoint(currMainImage.width() - 1, curr_y));

		for (int j = 0; j < m_duplicate_time; ++j) {
			QRect leftTarget(QPoint(m_duplicate_time * count + j, 0), QPoint(m_duplicate_time * count + j, currMainImage.height() - 1));
			leftPainter.drawImage(leftTarget, currMainImage, leftSource);

			QRect vertTarget(QPoint(0, m_duplicate_time * count + j), QPoint(currMainImage.width() - 1, m_duplicate_time * count + j));
			vertPainter.drawImage(vertTarget, currMainImage, vertSource);
		}
	}


	leftPainter.end();
	vertPainter.end();


}





QImage ThreeView::getLeftViewImage() const
{
	return left_view_image;
}







QImage ThreeView::getVerticalViewImage() const
{
	return vertical_view_image;
}








QImage ThreeView::getMainViewImage() const
{
	if (m_curr_image_index >=0 && m_curr_image_index < m_all_images.size())
		return m_all_images[m_curr_image_index];
	else {
		return QImage();
	}
}









void ThreeView::setAllImages(QList<QImage>& images)
{
	m_all_images.clear();
	for (QImage image: images) {
		if (image.width() > max_width) {
			max_width = image.width();
		}
		if (image.height() > max_height) {
			max_height = image.height();
		}
		m_all_images.append(image);
	}

	//transformImageToMat();
}









void ThreeView::setRangeOfImages(int range)
{
	if (range < 0)
		return;
	m_range_of_images = range;
}










void ThreeView::setCurrImageIndex(int index)
{
	if (index >= m_all_images.size()) {
		m_curr_image_index = m_all_images.size()-1;
		return;
	}
	if (index < 0) {
		m_curr_image_index = 0;
		return;
	}
	m_curr_image_index = index;
}








void ThreeView::setCurrPoint(QPoint point)
{
	if (point.x() < 0 || point.x() >= max_width || point.y() < 0 || point.y() >= max_height)
		return;
	m_curr_point = point;
}







void ThreeView::setDuplicatedTime(int d_time)
{
	m_duplicate_time = d_time;
}








void ThreeView::setCurrRelativePoint(double x, double y)
{
	int rx = x * max_width;
	int ry = y * max_height;
	setCurrPoint(QPoint(rx,ry));
}






//void ThreeView::transformImageToMat()
//{
//	m_all_mats.clear();

//	for (QImage image: m_all_images) {
//		//为避免矩阵运算错误，事先统一Image的大小
//		cv::Mat mat = QImageToMat(image);

//		if  (mat.rows < max_height) {
//			cv::Mat addMat = cv::Mat::zeros(max_height - mat.rows, mat.cols, mat.type());
//			cv::vconcat(addMat, mat, mat);
//		}
//		if (mat.cols < max_width) {
//			cv::Mat addMat = cv::Mat::zeros(mat.rows, max_width - mat.cols, mat.type());
//			cv::hconcat(addMat, mat, mat);
//		}
//		m_all_mats.append(mat);
//	}
//	qDebug() << "size: " << m_all_mats.size();
//}








//cv::Mat ThreeView::QImageToMat(const QImage& image)
//{
//	cv::Mat mat;
//		qDebug() << image.format();
//		switch(image.format())
//		{
//		case QImage::Format_ARGB32:
//		case QImage::Format_RGB32:
//		case QImage::Format_ARGB32_Premultiplied:
//			mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
//			break;
//		case QImage::Format_RGB888:
//			mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
//			cv::cvtColor(mat, mat, CV_BGR2RGB);
//			break;
//		case QImage::Format_Indexed8:
//			mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
//			break;
//		}
//		return mat;

//}









//QImage ThreeView::MatToQImage(const cv::Mat& mat)
//{
//	// 8-bits unsigned, NO. OF CHANNELS = 1
//		if(mat.type() == CV_8UC1)
//		{
//			QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
//			// Set the color table (used to translate colour indexes to qRgb values)
//			image.setColorCount(256);
//			for(int i = 0; i < 256; i++)
//			{
//				image.setColor(i, qRgb(i, i, i));
//			}
//			// Copy input Mat
//			uchar *pSrc = mat.data;
//			for(int row = 0; row < mat.rows; row ++)
//			{
//				uchar *pDest = image.scanLine(row);
//				memcpy(pDest, pSrc, mat.cols);
//				pSrc += mat.step;
//			}
//			return image;
//		}
//		// 8-bits unsigned, NO. OF CHANNELS = 3
//		else if(mat.type() == CV_8UC3)
//		{
//			// Copy input Mat
//			const uchar *pSrc = (const uchar*)mat.data;
//			// Create QImage with same dimensions as input Mat
//			QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
//			return image.rgbSwapped();
//		}
//		else if(mat.type() == CV_8UC4)
//		{
//			// Copy input Mat
//			const uchar *pSrc = (const uchar*)mat.data;
//			// Create QImage with same dimensions as input Mat
//			QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
//			return image.copy();
//		}
//		else
//		{
//			return QImage();
//		}
//}
