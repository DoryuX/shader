#include "mainwindow.h"

MainWindow::MainWindow ( QMainWindow *parent )
    : QMainWindow(parent)
{
    setWindowTitle ( "spheres" );

    createActions();
    createMenus();

    QWidget *cw = new QWidget(this);
    QWidget *w = new QWidget(cw);
    nSpinner = new QSpinBox(w);
    nSpinner->setRange(0,50);
    nSpinner->setValue(5);
    QVBoxLayout *vlayout = new QVBoxLayout(w);
    vlayout->addWidget(nSpinner);
    vlayout->addStretch();
    gl = new glWidget(cw);
    QHBoxLayout *layout = new QHBoxLayout(cw);
    layout->addWidget(w,0);
    layout->addWidget(gl,1);
    setCentralWidget ( cw );

    connect ( nSpinner, SIGNAL(valueChanged(int)), gl, SLOT(setN(int)) );
}

void MainWindow::createActions()
{
    openAction = new QAction(tr("&Open..."),this);
    openAction->setStatusTip(tr("Open file"));
    connect ( openAction, SIGNAL(triggered()), this, SLOT(open()) );

    aboutAction = new QAction(tr("&About spheres"),this);
    aboutAction->setStatusTip(tr("Information about spheres"));
    connect ( aboutAction, SIGNAL(triggered()), this, SLOT(about()) );
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
}

void MainWindow::open()
{
    QMessageBox::information(this, tr("Open"), tr("Would open"));
}

void MainWindow::about()
{
    QMessageBox::information(this, tr("About Spheres"),
        tr("Spheres <br>Ray Seyfarth"));
}

