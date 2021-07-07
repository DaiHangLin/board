#include "mainwindow.h"
#include "myscene.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    QGraphicsScene *scene = new QGraphicsScene(QRectF(0, 0, 800, 800));
//    scene->addLine(0, 0, 100, 100);
//    QGraphicsView *view = new QGraphicsView(scene);
//    view->show();

    MyScene scene;

    return a.exec();
}
