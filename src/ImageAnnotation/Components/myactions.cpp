 #include "myactions.h"
#include <QDebug>
MyActions::MyActions(QObject *parent) : QAction(parent)
{
}
MyActions::~MyActions() {}

OpenFileAction::OpenFileAction(QObject *parent) : MyActions (parent) {
	setIcon(QIcon(":/Image/Icon/open_file"));
	setText("&Open");
	setShortcuts(QKeySequence::Open);
}


OpenDirAction::OpenDirAction(QObject *parent) : MyActions (parent) {
	setIcon(QIcon(":/Image/Icon/open_dir"));
	setText("Open Dir");
}


PrevImageAction::PrevImageAction(QObject *parent) : MyActions (parent) {
	setIcon(QIcon(":/Image/Icon/prev_image"));
	setText("&Prev Image");
	setShortcut(tr("Shift+Tab"));
}

NextImageAction::NextImageAction(QObject *parent) : MyActions (parent) {
	setIcon(QIcon(":/Image/Icon/next_image"));
	setText("&Next Image");
	setShortcut(tr("Tab"));
}

SaveAsAction::SaveAsAction(QObject *parent) : MyActions (parent) {
	setIcon(QIcon(":/Image/Icon/save_all"));
	setText("Save All");
	setShortcuts(QKeySequence::SaveAs);
}

DeleteLabelAction::DeleteLabelAction(QObject *parent) : MyActions (parent) {
	setIcon(QIcon(":/Image/Icon/delete_label"));
	setText("&Delete Label");
	setShortcuts(QKeySequence::Delete);
}

CloseFileAction::CloseFileAction(QObject *parent) : MyActions (parent) {
	setIcon(QIcon(":/Image/Icon/close_file"));
	setText("&Close File");
	setShortcuts(QKeySequence::Close);
}

RectModeAction::RectModeAction(QObject *parent) : MyActions (parent) {
	setIcon(QIcon(":/Image/Icon/rect_mode"));
	setText("&Rectangle");
	setShortcut(tr("Ctrl+R"));
}

EllipseModeAction::EllipseModeAction(QObject *parent) : MyActions (parent) {
	setIcon(QIcon(":/Image/Icon/ellipse_mode"));
	setText("&Ellipse");
	setShortcut(tr("Ctrl+E"));
}

PolygonModeAction::PolygonModeAction(QObject *parent) : MyActions (parent) {
	setIcon(QIcon(":/Image/Icon/polygon_mode"));
	setText("&Polygon");
	setShortcut(tr("Ctrl+P"));
}

CurveModeAction::CurveModeAction(QObject *parent) : MyActions (parent){
	setIcon(QIcon(":/Image/Icon/curve_mode"));
	setText("&Curve");
	setShortcut(tr("Ctrl+C"));
}

SquarePenModeAction::SquarePenModeAction(QObject *parent) : MyActions (parent){
	setIcon(QIcon(":/Image/Icon/square_pen_mode"));
	setText("Square Brush");
}

CirclePenModeAction::CirclePenModeAction(QObject *parent) : MyActions (parent){
	setIcon(QIcon(":/Image/Icon/circle_pen_mode"));
	setText("Circle Brush");
}

CurseModeAction::CurseModeAction(QObject* parent): MyActions (parent){
	setIcon(QIcon(":/Image/Icon/curse_mode"));
	setText("Curse");
	setShortcut(tr("Ctrl+X"));
}

ThreeDModeAction::ThreeDModeAction(QObject* parent) : MyActions (parent){
	setIcon(QIcon(":/Image/Icon/3D_mode"));
	setText("3D");
}

TwoDModeAction::TwoDModeAction(QObject* parent): MyActions (parent){
	setIcon(QIcon(":/Image/Icon/2D_mode"));
	setText("2D");
}

MagnifyAction::MagnifyAction(QObject* parent): MyActions (parent){
	setIcon(QIcon(":/Image/Icon/magnify"));
	setText("Magnify");
}

ImportAction::ImportAction(QObject* parent): MyActions (parent)
{
	setIcon((QIcon(":/Image/Icon/import")));
	setText("Import");
}

SaveAction::SaveAction(QObject* parent): MyActions (parent)
{
	setIcon(QIcon(":/Image/Icon/save"));
	setText("&Save");
	setShortcuts(QKeySequence::Save);
}

UndoAction::UndoAction(QObject* parent): MyActions (parent)
{
	setIcon(QIcon(":/Image/Icon/undo"));
	setText("Undo");
	setShortcuts(QKeySequence::Undo);
}
RedoAction::RedoAction(QObject* parent): MyActions (parent)
{
	setIcon(QIcon(":/Image/Icon/redo"));
	setText("Redo");
	setShortcuts(QKeySequence::Redo);
}
