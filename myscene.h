#ifndef MYSCENE_H
#define MYSCENE_H

#include "myitem.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>



class MyScene: public QGraphicsScene
{
    Q_OBJECT

public:
    MyScene();
    ~MyScene() override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    void init();

private:
    QGraphicsView *view;
    MyItem *item;
};

#endif // MYSCENE_H
