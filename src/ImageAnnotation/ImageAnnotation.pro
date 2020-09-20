#-------------------------------------------------
#
# Project created by QtCreator 2019-08-25T14:59:34
#
#-------------------------------------------------

QT       += core gui
QT		 += xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageAnnotation
TEMPLATE = app



SOURCES += \
	Algorithms/threeview.cpp \
	Components/drawfinisheddialog.cpp \
	Components/filelistdockwidget.cpp \
	Components/labelsdockwidget.cpp \
	Components/labeltypedockwidget.cpp \
	Components/magnifyingglass.cpp \
	Components/menubar.cpp \
	Components/mygraphicsitems.cpp \
	Components/mygraphicsview.cpp \
	Components/statusbar.cpp \
	Components/myactions.cpp \
	Components/toolbar.cpp \
	Controllers/area.cpp \
	Controllers/areacontroller.cpp \
	Controllers/circlepen.cpp \
	Controllers/curve.cpp \
	Controllers/ellipse.cpp \
	Controllers/filecontroller.cpp \
	Controllers/label.cpp \
	Controllers/labelcontroller.cpp \
	Controllers/mycommand.cpp \
	Controllers/paintscene.cpp \
	Controllers/polygon.cpp \
	Controllers/rect.cpp \
	Controllers/shape.cpp \
	Controllers/squarepen.cpp \
        main.cpp \
		mainwindow.cpp


HEADERS += \
	Algorithms/threeview.h \
	Components/drawfinisheddialog.h \
	Components/filelistdockwidget.h \
	Components/labelsdockwidget.h \
	Components/labeltypedockwidget.h \
	Components/magnifyingglass.h \
	Components/menubar.h \
	Components/myactions.h \
	Components/mygraphicsitems.h \
	Components/mygraphicsview.h \
	Components/statusbar.h \
	Components/myactions.h \
	Components/toolbar.h \
	Controllers/area.h \
	Controllers/areacontroller.h \
	Controllers/circlepen.h \
	Controllers/curve.h \
	Controllers/ellipse.h \
	Controllers/filecontroller.h \
	Controllers/label.h \
	Controllers/labelcontroller.h \
	Controllers/mycommand.h \
	Controllers/paintscene.h \
	Controllers/polygon.h \
	Controllers/rect.h \
	Controllers/shape.h \
	Controllers/squarepen.h \
		mainwindow.h


FORMS += \
        Components/drawfinisheddialog.ui \
        Components/statusbar.ui \
        mainwindow.ui

RESOURCES += \
	resource.qrc

