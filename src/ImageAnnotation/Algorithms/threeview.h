#ifndef THREEVIEW_H
#define THREEVIEW_H

#include <QList>
#include <QImage>
#include <QPixmap>
#include <QPoint>
#include <QDir>
#include <QDirIterator>
#include <QObject>

#include "Controllers/shape.h"

/*
 * input a series of ORDERED SLIDED images of one view, a point at current image
 * output the other two views(image)
*/

class ThreeView :public QObject
{
	Q_OBJECT

	int m_range_of_images;// 选中当前图片的前/后多少张用于重建其他2个视图，与粒度共同决定生成图片的大小；粒度为4时，30~40张图片为合理值（4*60~80像素）
	int m_duplicate_time;// 一行/列像素被复制的次数，这个值越大则说明切片的粒度越大
	int m_curr_image_index;

	//用于统一图片大小
	int max_width = 0;
	int max_height = 0;

	//所有切片列表
	QList<QImage> m_all_images;
	//QList<cv::Mat> m_all_mats;

	QPoint m_curr_point;

	QImage left_view_image;
	QImage vertical_view_image;

	//cv::Mat main_view_mat;// Main view
	//cv::Mat left_view_mat;// Left view
	//cv::Mat vertical_view_mat;// Vertical view



	//cv::Mat QImageToMat(const QImage& image);
	//QImage MatToQImage(const cv::Mat& mat);
	//void transformImageToMat();
public:
	ThreeView() = delete;
	ThreeView(int range_of_images, int duplicate_time, QObject* parent = nullptr) :
		 m_range_of_images(range_of_images), m_duplicate_time(duplicate_time) ,QObject (parent){

	}

	void generate();

	QImage getLeftViewImage() const;
	QImage getVerticalViewImage() const;
	QImage getMainViewImage() const;
public slots:
	// 输入所有切片
	void setAllImages(QList<QImage>& images);
	// 设置复原用的图片范围
	void setRangeOfImages(int range);
	// 设置当前主视图图片下标
	void setCurrImageIndex(int index);
	// 设置当前主视图鼠标位置
	void setCurrPoint(QPoint point);
	// 设置鼠标位置（百分比）
	void setCurrRelativePoint(double x, double y);

	void setDuplicatedTime(int d_time);



};

#endif // THREEVIEW_H
