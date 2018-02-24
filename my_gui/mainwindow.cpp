#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent)
{
    setWindowTitle(tr("Main Window"));
    graphicsScene=new graphscene;
    createActions();
    createMenu();
    createToolBar();
    createToolBox();
    statusBar();
    createLayOut();
}

MainWindow::~MainWindow()
{
    delete graphicsScene;
}

//---------------------------------------------INTERFACE-------------------------------------------------------

void MainWindow::createActions()
{
    openAction = new QAction(QIcon(":/images/doc-open.png"),tr("&Open.."),this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing filde"));
    connect(openAction,&QAction::triggered,this,&MainWindow::open);

    saveAction = new QAction(tr("&Save"),this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save a new file"));
    connect(saveAction,&QAction::triggered,this,&MainWindow::save);

    initAction = new QAction(tr("&Initial"),this);
    initAction->setStatusTip(tr("Initial vertex"));
    connect(initAction,&QAction::triggered,this,&MainWindow::initVertrx);
}

void MainWindow::createMenu()
{
    QMenu* file = menuBar()->addMenu(tr("&File"));
    file->addAction(openAction);
    file->addAction(saveAction);
    QMenu* display = menuBar()->addMenu(tr("&Display"));
    display->addAction(initAction);
}

void MainWindow::createToolBar()
{
    QToolBar* toolBar=addToolBar(tr("&File"));
    toolBar->addAction(openAction);
    toolBar->addAction(saveAction);
}

void MainWindow::createToolBox()
{
    QVBoxLayout* graphlayout=new QVBoxLayout;
    graphlayout->setSpacing(10);
    QWidget* graphwidget=new QWidget;
    QWidget* xyzwidget=XYZWidget();

    QSpinBox* pointnumber=new QSpinBox(graphwidget);
    pointnumber->setRange(0,3000);
    pointnumber->setValue(500);
    connect(pointnumber,static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,&MainWindow::setPointNumber);
    QFormLayout* pointlayout=new QFormLayout;
    pointlayout->addRow(QString(tr("Point Number:")),pointnumber);

    QCheckBox* ifshowregion=new QCheckBox(tr("Show Region"),graphwidget);
    ifshowregion->setChecked(true);
    QCheckBox* ifshowpoint=new QCheckBox(tr("Show Points"),graphwidget);
    QCheckBox* ifshowmesh=new QCheckBox(tr("Show Meshes"),graphwidget);
    connect(ifshowregion,&QCheckBox::toggled,graphicsScene,&graphscene::setRegionState);
    connect(ifshowpoint,&QCheckBox::toggled,graphicsScene,&graphscene::setPointState);

    graphlayout->addWidget(xyzwidget);
    graphlayout->addLayout(pointlayout);
    graphlayout->addWidget(ifshowregion);
    graphlayout->addWidget(ifshowpoint);
    graphlayout->addWidget(ifshowmesh);
    graphlayout->addStretch();
    graphwidget->setLayout(graphlayout);

    QVBoxLayout* iterlayout=new QVBoxLayout;
    QWidget* iterwidget=new QWidget;
    QSlider* slider2=new QSlider(Qt::Horizontal,iterwidget);
    slider2->setRange(0,100);
    iterlayout->addWidget(slider2);
    iterwidget->setLayout(iterlayout);

    toolBox=new QToolBox;
    toolBox->setFixedWidth(200);
    //toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->setMinimumWidth(xyzwidget->sizeHint().width());
    toolBox->addItem(graphwidget,tr("Graphics"));
    toolBox->addItem(iterwidget,tr("Iteration"));
}

void MainWindow::createLayOut()
{
    QHBoxLayout* layout=new QHBoxLayout;
    layout->addWidget(toolBox);

   // graphicsScene=new graphscene();
    graphicsScene->setFixedSize(600,600);
    layout->addWidget(graphicsScene);
    QWidget* widget=new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
}


QWidget* MainWindow::XYZWidget()
{
    xLineEdit=new QLineEdit;
    xLineEdit->setMaximumWidth(48);
    xLineEdit->setValidator(new QIntValidator(0,360));
    connect(graphicsScene,&graphscene::xRotationChanged,xLineEdit,&QLineEdit::setText);
    connect(xLineEdit,&QLineEdit::textChanged,graphicsScene,&graphscene::setXRotation);
    yLineEdit=new QLineEdit;
    yLineEdit->setMaximumWidth(48);
    yLineEdit->setValidator(new QIntValidator(0,360));
    connect(graphicsScene,&graphscene::yRotationChanged,yLineEdit,&QLineEdit::setText);
    connect(yLineEdit,&QLineEdit::textChanged,graphicsScene,&graphscene::setYRotation);
    zLineEdit=new QLineEdit;
    zLineEdit->setMaximumWidth(48);
    zLineEdit->setValidator(new QIntValidator(0,360));
    connect(graphicsScene,&graphscene::zRotationChanged,zLineEdit,&QLineEdit::setText);
    connect(zLineEdit,&QLineEdit::textChanged,graphicsScene,&graphscene::setZRotation);

    QFormLayout* xlayout=new QFormLayout;
    QFormLayout* ylayout=new QFormLayout;
    QFormLayout* zlayout=new QFormLayout;
    xlayout->addRow(QString(tr("x:")),xLineEdit); xlayout->setMargin(0);
    ylayout->addRow(QString(tr("y:")),yLineEdit); ylayout->setMargin(0);
    zlayout->addRow(QString(tr("z:")),zLineEdit); zlayout->setMargin(0);

    QHBoxLayout* xyzlayout=new QHBoxLayout;
    xyzlayout->addLayout(xlayout);
    xyzlayout->addLayout(ylayout);
    xyzlayout->addLayout(zlayout);
    QWidget* xyzwidget=new QWidget;
    xyzwidget->setLayout(xyzlayout);
    return xyzwidget;
}

//---------------------------------------------SLOTS-------------------------------------------------------

void MainWindow::setPointNumber(int n)
{
    graphicsScene->vertex_number_=n;
}

//---------------------------------------------FUNCTIONS-------------------------------------------------------
void MainWindow::open()
{
    //graphicsScene->tet=new YHGE::MyTetStruct;
    QString path=QFileDialog::getOpenFileName(this,
                                              tr("Open File"),
                                              ".",
                                              tr("Object File(*.obj)"));
    if(!path.isEmpty())
    {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            QMessageBox::warning(this,tr("Read File"),
                                 tr("Cannot open file:\n%1").arg(path));
            return;
        }
        graphicsScene->tet->load(path.toStdString());
        graphicsScene->paintGL();
        graphicsScene->update();
        //QTextStream in(&file);
        //textEdit->setText(in.readAll());
    }
    else
    {
        QMessageBox::warning(this,tr("Path"),
                             tr("You did not select any file."));
    }
//    QDialog qd(this);
//    qd.setWindowTitle(tr("hello,dialog"));
//    qd.exec();
//   // QMessageBox::information(this,tr("Information"),tr("Open"));
}

void MainWindow::save()
{
    QString path = QFileDialog::getSaveFileName(this,
                                                tr("Open File"),
                                                ".",
                                                tr("Text Files(*txt)"));
    if(!path.isEmpty())
    {
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QMessageBox::warning(this,tr("Write File"),
                                 tr("Cannot open file:\n%1").arg(path));
            return;
        }
        QTextStream out(&file);
        out<<textEdit->toPlainText();
        file.close();
    }
    else
    {
        QMessageBox::warning(this,tr("Path"),
                             tr("You did not select any file."));
    }

}

void   MainWindow::initVertrx()
{
    graphicsScene->tet->init_boundary_points(graphicsScene->vertex_number_);
    graphicsScene->update();
}
