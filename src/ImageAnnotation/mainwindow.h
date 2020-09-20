#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDockWidget>
#include <QMainWindow>
#include <QtDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QImage>
#include <QList>
#include <QImageReader>
#include "Components/menubar.h"
#include "Components/toolbar.h"
#include "Components/myactions.h"
#include "Controllers/paintscene.h"
#include "Components/statusbar.h"
#include "Controllers/shape.h"
#include "Components/filelistdockwidget.h"
#include "Components/labelsdockwidget.h"
#include "Components/labeltypedockwidget.h"
#include "Controllers/filecontroller.h"
#include "Controllers/labelcontroller.h"
#include "Components/drawfinisheddialog.h"
#include "Controllers/areacontroller.h"
#include "Components/graphicsview.h"
#include "Components/mygraphicsview.h"
#include "Algorithms/threeview.h"
#include "Components/magnifyingglass.h"
#include "Controllers/mycommand.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
	void onOpenFileTriggered();
	void onOpenDirTriggered();
	void onSaveAsTriggered();
	void onCloseFileTriggered();
	void onNextImageTriggered();
	void onPrevImageTriggered();
	void onRectModeTriggered();
	void onEllipseModeTriggered();
	void onPolygonModeTriggered();
	void onCurveModeTriggered();
	void onSquarePenModeTriggered();
	void onCirclePenModeTriggered();
	void onCurseModeTriggered();
	void on3DModeTriggered();
	void on2DModeTriggered();
	void drawFinishedSlot(Shape* shape);
	void onDrawFinishedButtonClicked();
	void onMagnifyTriggered();
	void onImportTriggered();
	void onSaveTriggered();
	void onUndoTriggered();
	void onRedoTriggered();
private:
    Ui::MainWindow *ui;

	MenuBar* menuBar;
	ToolBar* toolBar;
	StatusBar* statusBar;

	DrawFinishedDialog* drawFinishedDialog;
	DrawFinishedDialog* drawFinishedDialog2D;
	DrawFinishedDialog* drawFinishedDialog3D;

	AreaController* areaController;
	AreaController* areaController2D;
	AreaController* areaController3D;

	FileController* fileController;
	LabelController* labelController;

	FileController* fileController2D;
	LabelController* labelController2D;

	FileController* fileController3D;
	LabelController* labelController3D;

	PaintScene *paintScene;
	MyGraphicsView *graphicsView;
	FileListDockWidget* fileListDockWidget;
	LabelsDockWidget* labelsDockWidget;
	LabelTypeDockWidget* labelTypeDockWidget;

	PaintScene *paintScene2D;
	MyGraphicsView *graphicsView2D;
	FileListDockWidget* fileListDockWidget2D;
	LabelsDockWidget* labelsDockWidget2D;
	LabelTypeDockWidget* labelTypeDockWidget2D;

	PaintScene *paintSceneMain;
	MyGraphicsView *graphicsViewMain;
	PaintScene* paintSceneLeft;
	MyGraphicsView *graphicsViewLeft;
	PaintScene *paintSceneVert;
	MyGraphicsView *graphicsViewVert;

	QWidget* centralWidget3D;
	QPushButton* drawFinishedButton;
	ThreeView* threeView;

	FileListDockWidget* fileListDockWidget3D;
	LabelsDockWidget* labelsDockWidget3D;
	LabelTypeDockWidget* labelTypeDockWidget3D;

	MagnifyingGlass* magnifying, *magnifying2D, *magnifying3D;

	QUndoStack* undoStack;
	QUndoStack* undoStack2D;
	QUndoStack* undoStack3D;

	enum Mode {
		NoMode,
		threeD,
		twoD
	};
	Mode currMode = NoMode;

};

#endif // MAINWINDOW_H
