#include "mycommand.h"
#define SAFE_DELETE(p) { if (p) { delete (p);     (p) = nullptr; } }


CreateLabelCommand::CreateLabelCommand(const QString& type, Area* area, LabelController* labelController, QUndoCommand* parent): QUndoCommand (parent)
{
	m_type = type;
	m_area = nullptr;
	if (area)
		m_area = area->clone();
	m_labelController = labelController;

	SAFE_DELETE(area);
}


CreateLabelCommand::~CreateLabelCommand()
{
	SAFE_DELETE(m_area);
}


//创建
void CreateLabelCommand::redo()
{
	if (!m_area)
		return;

	Area *area = m_area->clone();
	Label* label = m_labelController->createLabel(m_type, area);

	if (label)
		m_id = label->getId();
}

//删除
void CreateLabelCommand::undo()
{
	m_labelController->deleteLabel(m_type, m_id);
}






DeleteCurrLabelCommand::DeleteCurrLabelCommand(LabelController* labelController, QString type, int id, QUndoCommand* parent): QUndoCommand (parent)
{

	m_type = type;
	m_id = id;
	Label* label = labelController->getLabel(type, id);
	m_labelController = labelController;
	m_label = nullptr;
	if (label)
		m_label = label->clone();
}

DeleteCurrLabelCommand::~DeleteCurrLabelCommand()
{
	SAFE_DELETE(m_label);
}


//删除当前
void DeleteCurrLabelCommand::redo()
{
	if (m_labelController)
		m_labelController->deleteLabel(m_type, m_id);
}



//回撤删除
void DeleteCurrLabelCommand::undo()
{
	if (!m_label)
		return;
	Label* label = m_label->clone();
	m_labelController->addLabel(label);
}




SwitchImageCommand::SwitchImageCommand(QString prevImageName, QString nextImageName, FileController* fileController, QUndoCommand* parent): QUndoCommand (parent)
{
	m_prev = prevImageName;
	m_next = nextImageName;
	m_fileController = fileController;
}



void SwitchImageCommand::redo()
{
	m_fileController->setCurrImageName(m_next);
}


void SwitchImageCommand::undo()
{
	m_fileController->setCurrImageName(m_prev);
}



CloseImageCommand::CloseImageCommand(FileController* fileController, QUndoCommand* parent): QUndoCommand (parent)
{
	m_fileController = fileController;
}

void CloseImageCommand::redo()
{
	m_imageName = m_fileController->getCurrImageName();
	m_imagePath = m_fileController->getCurrImagePath();
	m_fileController->removeFile(m_imageName);
}

void CloseImageCommand::undo()
{
	m_fileController->openFileByPath(m_imagePath);
}


