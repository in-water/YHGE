#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QAction>
#include <QCheckBox>
#include <QDebug>
#include <QFileDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QSlider>
#include <QSpinBox>
#include <QTextEdit>
#include <QToolBar>
#include <QToolBox>
#include <QValidator>
#include <QVBoxLayout>

#include "graphic_scene.h"

class MainWindow:public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent=0);
    ~MainWindow();

private slots:
    void setPointNumber(int n);

private:
    void createActions();
    void createMenu();
    void createToolBar();
    void createToolBox();
    void createLayOut();
    void open();
    void save();
    void initVertrx();

    QWidget* XYZWidget();

    QAction* openAction;
    QAction* saveAction;
    QAction* initAction;
    QTextEdit* textEdit;
    QToolBox*   toolBox;
    graphscene* graphicsScene;
    QLineEdit *xLineEdit,*yLineEdit,*zLineEdit;
};

#endif // MAINWINDOW_H
