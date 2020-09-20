#ifndef MYCOMMAND_H
#define MYCOMMAND_H


#include <QUndoCommand>
#include <QDomDocument>
#include "Controllers/paintscene.h"
#include "Controllers/labelcontroller.h"
#include "Controllers/filecontroller.h"
#include "Controllers/areacontroller.h"
#include "Components/mygraphicsitems.h"



/*
 * Undo/Redo指令类
 * 支持的Undo/Redo有Label的创建、删除与图片的切换
*/


class CreateLabelCommand :public QUndoCommand
{
public :
	CreateLabelCommand(const QString& type, Area* area, LabelController* labelController, QUndoCommand* parent = nullptr);
	~CreateLabelCommand();
	// 创建一个label
	void redo() override;
	// 撤销创建一个label
	void undo() override;
private:
	QString m_type;// 保存type
	int m_id;// 保存id
	Area* m_area;// 保存area信息
	LabelController* m_labelController;
};



class DeleteCurrLabelCommand :public QUndoCommand
{
public :
	DeleteCurrLabelCommand(LabelController* labelController, QString type, int id, QUndoCommand* parent = nullptr);
	~DeleteCurrLabelCommand();
	// 删除当前label
	void redo() override;
	// 撤销删除label
	void undo() override;
private:
	QString m_type;
	int m_id;
	Label* m_label;
	LabelController* m_labelController;
};

class SwitchImageCommand : public QUndoCommand
{
public :
	SwitchImageCommand(QString prevImageName, QString nextImageName, FileController* fileController, QUndoCommand* parent = nullptr);
	// 切换
	void redo() override;
	// 换回
	void undo() override;
private:
	QString m_prev, m_next;
	FileController* m_fileController;
};

class CloseImageCommand : public QUndoCommand
{
public :
	CloseImageCommand(FileController* fileController, QUndoCommand* parent = nullptr);
	// 关闭
	void redo() override;
	// 打开
	void undo() override;
private:
	FileController* m_fileController;
	QString m_imageName;
	QString m_imagePath;
};





#endif // MYCOMMAND_H
