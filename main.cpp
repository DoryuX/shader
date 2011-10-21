#include <QApplication>
#include <stdlib.h>

#include "widgets/mainwindow.h"

int main ( int argc, char **argv )
{
    int n;
    double max_radius;
    int rotate;



    QApplication app(argc,argv);
    Q_INIT_RESOURCE(resources);

    MainWindow w;
    w.show();
    n = argc > 1 ? atof(argv[1]) : 5;

    // Always start with rotation.
    rotate = argc > 2;

    max_radius = (n < 20) ? 400 : 20;
    max_radius = (n < 100000)? max_radius: 10;
    w.gl->setRotate ( rotate );
    w.gl->setMaxRadius ( max_radius );
    w.gl->setNumCylinders ( n );

    // Level of Detail
    w.gl->setN(24);

    return app.exec();
}
