#include "mainwindow.h"
#include "ui_mainwindow.h"

#define SAFE_DELETE(p) { if (p) { delete (p);     (p) = nullptr; } }

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Image Annotation");
    QWidget* c = this->takeCentralWidget();
    if (c) delete c;

    threeView = new ThreeView(40, 4, this);//3D视图初始参数


    undoStack2D = new QUndoStack(this);
    undoStack3D = new QUndoStack(this);




    statusBar = new StatusBar(this);
    this->setStatusBar(statusBar);






    auto openFileAction = new OpenFileAction(this);
    connect(openFileAction, &OpenFileAction::triggered,
            this, &MainWindow::onOpenFileTriggered);

    auto openDirAction = new OpenDirAction(this);
    connect(openDirAction, &OpenDirAction::triggered,
            this, &MainWindow::onOpenDirTriggered);

    auto saveAction = new SaveAction(this);

    connect(saveAction, &SaveAsAction::triggered,
            this, &MainWindow::onSaveTriggered);

    auto saveAsAction = new SaveAsAction(this);
    connect(saveAsAction, &SaveAsAction::triggered,
            this, &MainWindow::onSaveAsTriggered);

    auto closeFileAction = new CloseFileAction(this);
    connect(closeFileAction, &CloseFileAction::triggered,
            this, &MainWindow::onCloseFileTriggered);

    auto importAction = new ImportAction(this);
    connect(importAction, &ImportAction::triggered,
            this, &MainWindow::onImportTriggered);

    auto nextImageAction = new NextImageAction(this);
    connect(nextImageAction, &NextImageAction::triggered,
            this, &MainWindow::onNextImageTriggered);

    auto prevImageAction = new PrevImageAction(this);
    connect(prevImageAction, &PrevImageAction::triggered,
            this, &MainWindow::onPrevImageTriggered);

    auto rectModeAction =  new RectModeAction(this);
    connect(rectModeAction, &RectModeAction::triggered,
            this, &MainWindow::onRectModeTriggered);

    auto ellipseModeAction = new EllipseModeAction(this);
    connect(ellipseModeAction, &EllipseModeAction::triggered,
            this, &MainWindow::onEllipseModeTriggered);

    auto deleteLabelAction = new DeleteLabelAction(this);
    connect(deleteLabelAction, &DeleteLabelAction::triggered,
            [=](){
        emit labelsDockWidget->deleteCurrLabel(labelsDockWidget->currLabelName());
    });

    auto polygonModeAction = new PolygonModeAction(this);
    connect(polygonModeAction, &PolygonModeAction::triggered,
            this, &MainWindow::onPolygonModeTriggered);

    auto curveModeAction = new CurveModeAction(this);
    connect(curveModeAction, &CurveModeAction::triggered,
            this, &MainWindow::onCurveModeTriggered);

    auto squarePenModeAction = new SquarePenModeAction(this);
    connect(squarePenModeAction, &SquarePenModeAction::triggered,
            this, &MainWindow::onSquarePenModeTriggered);

    auto circlePenModeAction = new CirclePenModeAction(this);
    connect(circlePenModeAction, &CirclePenModeAction::triggered,
            this, &MainWindow::onCirclePenModeTriggered);

    auto curseModeAction = new CurseModeAction(this);
    connect(curseModeAction, &CurseModeAction::triggered,
            this, &MainWindow::onCurseModeTriggered);

    auto twoDModeAction = new TwoDModeAction(this);
    connect(twoDModeAction, &TwoDModeAction::triggered,
            this, &MainWindow::on2DModeTriggered);

    auto threeDModeAction = new ThreeDModeAction(this);
    connect(threeDModeAction, &ThreeDModeAction::triggered,
            this, &MainWindow::on3DModeTriggered);

    auto magnifyAction = new MagnifyAction(this);
    connect(magnifyAction, &MagnifyAction::triggered,
            this, &MainWindow::onMagnifyTriggered);

    auto undoAction = new UndoAction(this);
    connect(undoAction, &MagnifyAction::triggered,
            this, &MainWindow::onUndoTriggered, Qt::ConnectionType::DirectConnection);

    auto redoAction = new RedoAction(this);
    connect(redoAction, &MagnifyAction::triggered,
            this, &MainWindow::onRedoTriggered, Qt::ConnectionType::DirectConnection);


    QActionGroup *drawingActionGroup = new QActionGroup(this);
    drawingActionGroup->addAction(curseModeAction);
    drawingActionGroup->addAction(rectModeAction);
    drawingActionGroup->addAction(ellipseModeAction);
    drawingActionGroup->addAction(polygonModeAction);
    drawingActionGroup->addAction(curveModeAction);
    drawingActionGroup->addAction(squarePenModeAction);
    drawingActionGroup->addAction(circlePenModeAction);

    QActionGroup *modeActionGroup = new QActionGroup(this);
    modeActionGroup->addAction(threeDModeAction);
    modeActionGroup->addAction(twoDModeAction);

    curseModeAction->setCheckable(true);
    curseModeAction->setChecked(true);
    circlePenModeAction->setCheckable(true);
    squarePenModeAction->setCheckable(true);
    rectModeAction->setCheckable(true);
    ellipseModeAction->setCheckable(true);
    curveModeAction->setCheckable(true);
    polygonModeAction->setCheckable(true);
    threeDModeAction->setCheckable(true);
    twoDModeAction->setCheckable(true);
    twoDModeAction->setChecked(true);
    magnifyAction->setCheckable(true);



    // set up and connect menu bar
    menuBar = new MenuBar(this);
    QMenu* menus[3];
    menus[0] = new QMenu("&File", menuBar);
    menus[1] = new QMenu("&Edit", menuBar);
    menus[2] = new QMenu("&View", menuBar);
   // menus[3] = new QMenu("&Help", menuBar);

    for (int i = 0; i < 3; i ++) {
        menuBar->addMenu(menus[i]);
    }

    menus[0]->addAction(openFileAction);
    menus[0]->addAction(openDirAction);
    menus[0]->addAction(saveAction);
    menus[0]->addAction(saveAsAction);
    menus[0]->addAction(importAction);
    menus[0]->addAction(closeFileAction);

    menus[1]->addAction(undoAction);
    menus[1]->addAction(redoAction);
    menus[1]->addAction(nextImageAction);
    menus[1]->addAction(prevImageAction);
    menus[1]->addAction(rectModeAction);
    menus[1]->addAction(ellipseModeAction);
    menus[1]->addAction(polygonModeAction);
    menus[1]->addAction(curveModeAction);
    menus[1]->addAction(squarePenModeAction);
    menus[1]->addAction(circlePenModeAction);

    menus[2]->addAction(magnifyAction);

    this->setMenuBar(menuBar);


    // set up tool bar
    toolBar = new ToolBar(this);
    toolBar->setIconSize(QSize(15, 15));
    toolBar->setFont(QFont("Console", 10,1));
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    QSlider* radiusSlider = new QSlider(Qt::Horizontal);
    radiusSlider->setParent(toolBar);
    radiusSlider->setRange(1,80);
    radiusSlider->setFixedWidth(60);
    QLabel* radiusLabel = new QLabel(toolBar);
    radiusLabel->setFont(QFont("微软雅黑",8,1));
    radiusLabel->setMargin(0);
    connect(radiusSlider, &QSlider::valueChanged,[=](int value) {
        radiusLabel->setText(QString::number(value));
    });

    QWidget *radiusWidget = new QWidget(toolBar);
    QHBoxLayout* radiusLayout = new QHBoxLayout(toolBar);
    radiusLayout->addWidget(radiusSlider);
    radiusLayout->addWidget(radiusLabel);
    radiusLayout->setMargin(0);
    radiusLayout->setSpacing(0);
    radiusWidget->setLayout(radiusLayout);



    toolBar->addAction(nextImageAction);
    toolBar->addAction(prevImageAction);
    toolBar->addAction(magnifyAction);
    toolBar->addAction(undoAction);
    toolBar->addAction(redoAction);
    toolBar->addSeparator();
    toolBar->addAction(curseModeAction);
    toolBar->addAction(rectModeAction);
    toolBar->addAction(ellipseModeAction);
    toolBar->addAction(polygonModeAction);
    toolBar->addAction(curveModeAction);
    toolBar->addAction(circlePenModeAction);
    toolBar->addAction(squarePenModeAction);
    toolBar->addWidget(radiusWidget);
    toolBar->addAction(deleteLabelAction);
    toolBar->addSeparator();
    toolBar->addAction(openFileAction);
    toolBar->addAction(openDirAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(saveAsAction);
    toolBar->addAction(importAction);
    toolBar->addAction(closeFileAction);
    toolBar->addSeparator();
    toolBar->addAction(twoDModeAction);
    toolBar->addAction(threeDModeAction);
    this->addToolBar(Qt::LeftToolBarArea, toolBar);








    // Init 2D
    labelTypeDockWidget2D = new LabelTypeDockWidget();
    labelsDockWidget2D = new LabelsDockWidget();
    fileListDockWidget2D = new FileListDockWidget();




    graphicsView2D = new MyGraphicsView();
    paintScene2D = new PaintScene();










    graphicsView2D->setScene(paintScene2D);
    graphicsView2D->fitInView(paintScene2D->sceneRect());
    graphicsView2D->setMouseTracking(true);




    connect(graphicsView2D, &MyGraphicsView::viewResized,
            [&]() {
        paintScene2D->changeCurrImage(fileController2D->getImage(fileController2D->getCurrImageName()));
        paintScene2D->updateShapes(labelController2D, fileController2D->getCurrImageName());
    });
    connect(paintScene2D, &PaintScene::scenePos,
            statusBar, &StatusBar::setScenePos);
    connect(paintScene2D, &PaintScene::mouseTrackingOn,
            [=] () {graphicsView2D->setMouseTracking(true);});
    connect(paintScene2D, &PaintScene::mouseTrackingOff,
            [=] () {graphicsView2D->setMouseTracking(false);});
    connect(paintScene2D, &PaintScene::drawFinished,
            this, &MainWindow::drawFinishedSlot, Qt::ConnectionType::DirectConnection);

    connect(radiusSlider, &QSlider::valueChanged,
            paintScene2D, &PaintScene::setRadius);
    //设置初始画笔半径
    radiusSlider->setValue(20);





    fileController2D = new FileController(this);

    connect(fileController2D, &FileController::fileAdded,
            fileListDockWidget2D, &FileListDockWidget::fileAdded);
    connect(fileController2D, &FileController::updateFiles,
            fileListDockWidget2D, &FileListDockWidget::openFileFinished);
    connect(fileController2D, &FileController::currImageChanged,
            [&](const QString& imageName) {
        paintScene2D->changeCurrImage(fileController2D->getImage(imageName));
        paintScene2D->updateShapes(labelController2D, imageName);
    });
    connect(fileController2D, &FileController::currImageChanged,
            [&](const QString& imageName) {
        labelsDockWidget2D->setLabelList(labelController2D->getLabelsOfImage(imageName));
    });
    connect(fileController2D, &FileController::fileRemoved,
            fileListDockWidget2D, &FileListDockWidget::fileClosed);




    labelController2D = new LabelController(this);

    connect(labelController2D, &LabelController::labelCreated,
            labelsDockWidget2D, &LabelsDockWidget::labelCreated);
    connect(labelController2D, &LabelController::labelCreated,
            [&]() {  paintScene2D->updateShapes(labelController2D, fileController2D->getCurrImageName());  });
    connect(labelController2D, &LabelController::labelDeleted,
            labelsDockWidget2D, &LabelsDockWidget::labelDeleted);
    connect(labelController2D, &LabelController::typeCreated,
            labelTypeDockWidget2D, &LabelTypeDockWidget::typeCreated);
    connect(labelController2D, &LabelController::typeDeleted,
            labelTypeDockWidget2D, &LabelTypeDockWidget::typeDeleted);
    connect(labelsDockWidget2D, &LabelsDockWidget::deleteCurrLabel,
            [&]() {
        QString currLabelName = labelsDockWidget2D->currLabelName();
        if (currLabelName == "")
            return;
        QStringList l = currLabelName.split("_");
        int id = l.last().toInt();
        l.pop_back();
        QString type = l.join("");
        DeleteCurrLabelCommand* deleteCurrLabelCommand = new DeleteCurrLabelCommand(labelController2D, type, id);
        undoStack2D->push(deleteCurrLabelCommand);
    });


    connect(paintScene2D, &PaintScene::itemSelected,
            [&](QGraphicsItem* item) {
        Label* label = labelController2D->findParentLabelOfItem(item);
        labelsDockWidget2D->labelSelected(label->getType() + "_" + QString::number(label->getId()));

    });
    connect(fileListDockWidget2D, &FileListDockWidget::itemClicked,
            [&](const QString& imageName) {
        SwitchImageCommand* switchImageCommand = new SwitchImageCommand(fileController2D->getCurrImageName(), imageName, fileController2D);
        undoStack2D->push(switchImageCommand);
    });
    connect(fileController2D, &FileController::currImageChanged,
            fileListDockWidget2D, &FileListDockWidget::selectItem);









    drawFinishedDialog2D = new DrawFinishedDialog(this);

    connect(drawFinishedDialog2D, &DrawFinishedDialog::sendTypeName,
            [&](QString& typeName) {
        QUndoCommand* createLabel = new CreateLabelCommand(typeName, areaController2D->takeArea(), labelController2D);
        undoStack2D->push(createLabel);
    });






    areaController2D = new AreaController(this);





    //Init 3D

    labelTypeDockWidget3D = new LabelTypeDockWidget();



    labelsDockWidget3D = new LabelsDockWidget();



    fileListDockWidget3D = new FileListDockWidget();








    centralWidget3D = new QWidget();
    graphicsViewMain = new MyGraphicsView(centralWidget3D);
    paintSceneMain = new PaintScene(centralWidget3D);

    graphicsViewMain->setScene(paintSceneMain);
    graphicsViewMain->fitInView(paintSceneMain->sceneRect());
    graphicsViewMain->setMouseTracking(true);





    graphicsViewLeft = new MyGraphicsView(centralWidget3D);
    paintSceneLeft = new PaintScene(centralWidget3D);

    graphicsViewLeft->setScene(paintSceneLeft);
    graphicsViewLeft->fitInView(paintSceneLeft->sceneRect());


    graphicsViewVert = new MyGraphicsView(centralWidget3D);
    paintSceneVert = new PaintScene(centralWidget3D);

    graphicsViewVert->setScene(paintSceneVert);
    graphicsViewVert->fitInView(paintSceneVert->sceneRect());



    graphicsViewMain->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    graphicsViewLeft->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    graphicsViewVert->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);



    drawFinishedButton = new QPushButton("Create Label");
    connect(drawFinishedButton, &QPushButton::clicked,
            this, &MainWindow::onDrawFinishedButtonClicked);



    //Layout
    QHBoxLayout* hl1 = new QHBoxLayout();
    hl1->setSpacing(10);
    hl1->setMargin(0);
    hl1->addWidget(graphicsViewMain, 2);
    hl1->addWidget(graphicsViewLeft, 1);
    QHBoxLayout* hl2 = new QHBoxLayout();
    hl2->setSpacing(10);
    hl2->setMargin(0);
    hl2->addWidget(graphicsViewVert, 2);
    hl2->addWidget(drawFinishedButton, 1);
    QVBoxLayout* vl = new QVBoxLayout();
    vl->addLayout(hl1, 2);
    vl->addLayout(hl2, 1);
    vl->setSpacing(10);
    vl->setMargin(0);
    centralWidget3D->setLayout(vl);






    connect(paintSceneMain, &PaintScene::sendCurrPosToThreeview,
            [&](double ratio_x, double ratio_y) {
        QString currImageName = fileController3D->getCurrImageName();
        threeView->setCurrRelativePoint(ratio_x, ratio_y);
        threeView->setCurrImageIndex(fileController3D->getIndexOfImage(currImageName));
        threeView->generate();
        paintSceneLeft->changeCurrImage(threeView->getLeftViewImage());
        paintSceneVert->changeCurrImage(threeView->getVerticalViewImage());
    });




    connect(graphicsViewMain, &MyGraphicsView::viewResized,
            [&]() {
        paintSceneMain->changeCurrImage(fileController3D->getImage(fileController3D->getCurrImageName()));
        paintSceneMain->updateShapes(labelController3D, fileController3D->getCurrImageName());
    });
    connect(graphicsViewLeft, &MyGraphicsView::viewResized,
            [&]() {
        paintSceneLeft->changeCurrImage(threeView->getLeftViewImage());
    });
    connect(graphicsViewVert, &MyGraphicsView::viewResized,
            [&]() {
        paintSceneLeft->changeCurrImage(threeView->getVerticalViewImage());
    });


    connect(paintSceneMain, &PaintScene::scenePos,
            statusBar, &StatusBar::setScenePos);

    connect(paintSceneMain, &PaintScene::mouseTrackingOn,
            [=] () {graphicsViewMain->setMouseTracking(true);});
    connect(paintSceneMain, &PaintScene::mouseTrackingOff,
            [=] () {graphicsViewMain->setMouseTracking(false);});

    connect(paintSceneMain, &PaintScene::drawFinished,
            this, &MainWindow::drawFinishedSlot, Qt::ConnectionType::DirectConnection);


    connect(radiusSlider, &QSlider::valueChanged,
            paintSceneMain, &PaintScene::setRadius);




    fileController3D = new FileController(this);


    connect(fileController3D, &FileController::fileAdded,
            fileListDockWidget3D, &FileListDockWidget::fileAdded);
    connect(fileController3D, &FileController::updateFiles,
            fileListDockWidget3D, &FileListDockWidget::openFileFinished);
    connect(fileController3D, &FileController::currImageChanged,
            [&](const QString& imageName) {
        fileListDockWidget3D->selectItem(imageName);
        paintSceneMain->changeCurrImage(fileController3D->getImage(imageName));
        paintSceneMain->updateShapes(labelController3D, imageName);
        paintSceneMain->updateShape(areaController3D->getCurrAreaShape(fileController->getCurrImageName()));

        paintSceneLeft->changeCurrImage(threeView->getLeftViewImage());
        paintSceneLeft->changeCurrImage(threeView->getVerticalViewImage());

    });


    connect(fileController3D, &FileController::updateFiles,
            [&]() {
        QList<QImage> images = fileController3D->getImages();
        threeView->setAllImages(images);
    });
    connect(fileController3D, &FileController::fileRemoved,
            fileListDockWidget3D, &FileListDockWidget::fileClosed);
    connect(fileController3D, &FileController::fileRemoved,
            [&]() {
        QList<QImage> images = fileController3D->getImages();
        threeView->setAllImages(images);
    });



    connect(fileController3D, &FileController::currImageChanged,
            [&](const QString& imageName) {  labelsDockWidget3D->setLabelList(labelController3D->getLabelsOfImage(imageName));  });











    labelController3D = new LabelController(this);


    connect(labelController3D, &LabelController::labelCreated,
            labelsDockWidget3D, &LabelsDockWidget::labelCreated);
    connect(labelController3D, &LabelController::labelCreated,
            [&]() {
        paintSceneMain->updateShapes(labelController3D, fileController3D->getCurrImageName());
        //TODO:paintSceneLeft, paintSceneRight?
    });
    connect(labelController3D, &LabelController::labelDeleted,
            labelsDockWidget3D, &LabelsDockWidget::labelDeleted);
    connect(labelController3D, &LabelController::typeCreated,
            labelTypeDockWidget3D, &LabelTypeDockWidget::typeCreated);
    connect(labelController3D, &LabelController::typeDeleted,
            labelTypeDockWidget3D, &LabelTypeDockWidget::typeDeleted);
    connect(labelsDockWidget3D, &LabelsDockWidget::deleteCurrLabel,
            //labelController3D, &LabelController::deleteCurrLabel);
            [&]() {
        QString currLabelName = labelsDockWidget3D->currLabelName();
        if (currLabelName == "")
            return;
        QStringList l = currLabelName.split("_");
        int id = l.last().toInt();
        l.pop_back();
        QString type = l.join("");
        DeleteCurrLabelCommand* deleteCurrLabelCommand = new DeleteCurrLabelCommand(labelController3D, type, id);
        undoStack3D->push(deleteCurrLabelCommand);
    });


    connect(fileListDockWidget3D, &FileListDockWidget::itemClicked,
            [&](const QString& imageName) {
        SwitchImageCommand* switchImageCommand = new SwitchImageCommand(fileController3D->getCurrImageName(), imageName, fileController3D);
        undoStack3D->push(switchImageCommand);
    });








    drawFinishedDialog3D = new DrawFinishedDialog(this);


    connect(drawFinishedDialog3D, &DrawFinishedDialog::sendTypeName,
            [&](QString& typeName) {
        QUndoCommand* createLabel = new CreateLabelCommand(typeName, areaController3D->takeArea(), labelController3D);
        undoStack3D->push(createLabel);
    });





    areaController3D = new AreaController(this);


    magnifying2D = new MagnifyingGlass();

    connect(paintScene2D, &PaintScene::scenePos,
            magnifying2D, &MagnifyingGlass::setDisplayPos);
    magnifying2D->setPaintScene(paintScene2D);

    magnifying3D = new MagnifyingGlass();
    connect(paintSceneMain, &PaintScene::scenePos,
            magnifying3D, &MagnifyingGlass::setDisplayPos);
    magnifying3D->setPaintScene(paintSceneMain);










    addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, labelTypeDockWidget2D);
    addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, labelsDockWidget2D);
    addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, fileListDockWidget2D);

    addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, labelTypeDockWidget3D);
    addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, labelsDockWidget3D);
    addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, fileListDockWidget3D);



    on2DModeTriggered();


}






MainWindow::~MainWindow()
{
    delete ui;
	SAFE_DELETE(magnifying2D);
	SAFE_DELETE(magnifying3D);
	SAFE_DELETE(centralWidget3D);
	SAFE_DELETE(graphicsView2D)
	SAFE_DELETE(paintScene2D);
}




void MainWindow::onOpenFileTriggered() {
	fileController->openFile(labelController);
}






void MainWindow::onOpenDirTriggered() {
	fileController->openDir(labelController);
}






void MainWindow::onSaveAsTriggered() {
	fileController->saveAsFile(labelController);
}






void MainWindow::onCloseFileTriggered() {
	CloseImageCommand* closeImageCommand = new CloseImageCommand(fileController);
	undoStack->push(closeImageCommand);
}






void MainWindow::onNextImageTriggered() {
	fileListDockWidget->nextFile();
}






void MainWindow::onPrevImageTriggered() {
	fileListDockWidget->prevFile();
}






void MainWindow::onRectModeTriggered() {
	paintScene->setCurrentShape(Shape::Figure::Rect);
}






void MainWindow::onEllipseModeTriggered() {
	paintScene->setCurrentShape(Shape::Figure::Ellipse);
}






void MainWindow::onPolygonModeTriggered() {
	paintScene->setCurrentShape(Shape::Figure::Polygon);
}






void MainWindow::onCurveModeTriggered() {
	paintScene->setCurrentShape(Shape::Figure::Curve);
}






void MainWindow::onSquarePenModeTriggered() {
	paintScene->setCurrentShape(Shape::Figure::SquarePen);
}






void MainWindow::onCirclePenModeTriggered() {
	paintScene->setCurrentShape(Shape::Figure::CirclePen);
}




void MainWindow::onCurseModeTriggered()
{
	paintScene->setCurrentShape(Shape::Figure::Empty);
}





void MainWindow::on3DModeTriggered()
{
	if (currMode == threeD) {
		return;
	}
	labelController = labelController3D;
	areaController = areaController3D;
	fileController = fileController3D;
	paintScene = paintSceneMain;
	drawFinishedDialog = drawFinishedDialog3D;
	undoStack = undoStack3D;

	labelsDockWidget2D->close();
	labelTypeDockWidget2D->close();
	fileListDockWidget2D->close();


	labelsDockWidget3D->show();
	labelTypeDockWidget3D->show();
	fileListDockWidget3D->show();
	labelTypeDockWidget = labelTypeDockWidget3D;
	labelsDockWidget = labelsDockWidget3D;
	fileListDockWidget = fileListDockWidget3D;

	takeCentralWidget();
	setCentralWidget(centralWidget3D);
	currMode = threeD;
}






void MainWindow::on2DModeTriggered()
{
	if (currMode == twoD) {
		return;
	}
	labelController = labelController2D;
	areaController = areaController2D;
	fileController = fileController2D;
	paintScene = paintScene2D;
	drawFinishedDialog = drawFinishedDialog2D;
	undoStack = undoStack2D;

	labelsDockWidget3D->close();
	labelTypeDockWidget3D->close();
	fileListDockWidget3D->close();


	labelsDockWidget2D->show();
	labelTypeDockWidget2D->show();
	fileListDockWidget2D->show();
	labelTypeDockWidget = labelTypeDockWidget2D;
	labelsDockWidget = labelsDockWidget2D;
	fileListDockWidget = fileListDockWidget2D;

	takeCentralWidget();
	setCentralWidget(graphicsView2D);
	currMode = twoD;
}








void MainWindow::drawFinishedSlot(Shape* shape) {
	if (!fileController->hasCurrImage())
		return;

	Shape* copyedShape = shape->clone();
	if (sender() == paintScene2D) {
		areaController2D->receiveImageShape(fileController->getCurrImageName(), copyedShape);

		drawFinishedDialog->setList(labelTypeDockWidget->getItemList());
		drawFinishedDialog->exec();
	}
	else if (sender() == paintSceneMain) {
		areaController3D->receiveImageShape(fileController->getCurrImageName(), copyedShape);
		paintSceneMain->updateShape(areaController3D->getCurrAreaShape(fileController->getCurrImageName()));
	}
	else {
		return;
	}
}









void MainWindow::onDrawFinishedButtonClicked()
{
	if (!areaController3D->hasCurrArea()) {
		return;
	}
	else {
		drawFinishedDialog->setList(labelTypeDockWidget->getItemList());
		drawFinishedDialog->exec();
	}
}








void MainWindow::onMagnifyTriggered()
{
	if (currMode == threeD) {
		magnifying = magnifying3D;
	}
	if (currMode == twoD) {
		magnifying = magnifying2D;
	}
	if (magnifying->isShowing())
		magnifying->close();
	else
		magnifying->show();
}




void MainWindow::onImportTriggered()
{
	fileController->importFromFile(labelController);
}





void MainWindow::onSaveTriggered()
{
	fileController->saveFile(labelController);
}


void MainWindow::onUndoTriggered()
{
	undoStack->undo();
}

void MainWindow::onRedoTriggered()
{
	undoStack->redo();
}


