#include "myscene.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

MyScene::MyScene()
{
    init();
}

MyScene::~MyScene()
{
    delete view;
}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//   qDebug() << "event" << event->scenePos() << event->pos() << event->screenPos();
   item->drawPress(event->scenePos());
   QGraphicsScene::mousePressEvent(event);
}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    item->drawMove(event->lastScenePos(), event->scenePos());
    QGraphicsScene::mouseMoveEvent(event);
}

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    item->drawRelease(event->scenePos());
    QGraphicsScene::mouseReleaseEvent(event);
}

void MyScene::init()
{
    this->setSceneRect(0,0,800,800);

    item = new MyItem(this->sceneRect());
    this->addItem(item);


    view = new QGraphicsView();
    view->move(0, 0);
    view->setScene(this);
    view->resize(900, 900);
//    view->setBackgroundBrush(QBrush(QColor(Qt::red)));
    view->show();
}
