#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QVBoxLayout>
#include "glwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow ( QMainWindow *parent=0 );
    glWidget *gl;

private slots:
    void open();
    void about();

private:
    QSpinBox *nSpinner;
    void createActions();
    void createMenus();
    void createControls();
    QMenu *fileMenu;
    QMenu *helpMenu;
    QAction *openAction;
    QAction *aboutAction;
};

#endif
