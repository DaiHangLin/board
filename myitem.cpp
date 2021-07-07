#include "myitem.h"
#include <QDebug>

MyItem::MyItem(QRectF r) : size(r.width(), r.height())
{
    initCanvas();
}

MyItem::~MyItem()
{

}

QRectF MyItem::boundingRect() const
{
    return QRectF(0, 0, size.width(), size.height());
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
   painter->setRenderHints(QPainter::SmoothPixmapTransform |
                           QPainter::Antialiasing);
   painter->drawImage(0, 0, *canvas);
}

void MyItem::initCanvas()
{
    canvas = new QImage(size.toSize(), QImage::Format_ARGB32_Premultiplied);
    canvas->fill(Qt::white);
    painter = new QPainter(canvas);

//    painter->drawLine(0,0, 300, 300);
//    drawPatchPath2(QPointF(300, 30), QPointF(400, 90));
}

void MyItem::drawPress(const QPointF &point)
{
    points.clear();
    points << point;
    drawPath();
}

void MyItem::drawMove(const QPointF &lp, const QPointF &p)
{
    points << p;
    drawPath();
}

void MyItem::drawRelease(const QPointF &p)
{
    points << p;
    drawPath();
}

void MyItem::drawPatchPath(QPointF p1, QPointF p2)
{
    int maxSeg = 50;
    qreal dx = p2.rx() - p1.rx();
    qreal dy = p2.ry() - p1.ry();

    qreal sx = dx / maxSeg;
    qreal sy = dy / maxSeg;

    qreal maxWidth = 16.0;
    qreal minWidth = 2.0;
    qreal dw = minWidth - maxWidth;
    qreal sw = dw / maxSeg;


    QPainterPath path;
    path.moveTo(p1 - QPointF(maxWidth / 2,  maxWidth / 2));
//    path.lineTo(300, 100);
//    QPainterPath p = strokePath(8, path);
//    painter->fillPath(p, Qt::red);

//    QPointF l1 = path.currentPosition();
//    path &= QPainterPath();
//    path.moveTo(l1);

//    QPainterPath p11 = strokePath(4, path);
//    painter->fillPath(p11, Qt::blue);

//    QPointF l2 = path.currentPosition();
//    path &= QPainterPath();
//    path.moveTo(l2);

//    path.lineTo(300, 200);

//    QPainterPath p12 = strokePath(2, path);
//    painter->fillPath(p12, Qt::black);
//    path &= QPainterPath(path.currentPosition());

    QPen pen(Qt::red, 8,
             Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QList<QColor> color;
    color << Qt::red << Qt::blue << Qt::black;
    for (int i = 1; i <= maxSeg; i ++) {
        qreal x = p1.rx() + sx * i;
        qreal y = p1.ry() + sy * i;
        qreal w = maxWidth + sw * i;
//        qDebug() << "x" << x << "y" << y << w;
//        path.quadTo(p1, (p1 + p2) / 2);
        path.lineTo(x - w / 2., y);

//        QPainterPath np = strokePath(w, path);
//        painter->fillPath(np, Qt::red);
        pen.setWidthF(w);
//        pen.setColor(color[i % 3]);
        painter->setPen(pen);

//        qDebug() << painter->pen().widthF() << painter->pen().color();
        qDebug() << "x" << x << "y" << y;

//        painter->drawPoint(x - 5, y - 5);

        painter->drawPath(path);
        QPointF cp = path.currentPosition();
        path &= QPainterPath();
        path.moveTo(cp);
    }
}

void MyItem::drawPatchPath2(QPointF p1, QPointF p2)
{
    QPainterPath path;
    path.moveTo(p1);
    path.lineTo(p2);
    qreal maxWidth = 6;
    qreal minwidth = 2;
    qreal dw = maxWidth - minwidth;
    qreal sw = dw / 100.;
    int k = 0;
    for (qreal i = 0; i <= 1; i += 0.01) {
        k++;
//        qDebug() << "w" << 8 - sw * i * 100 << sw << sw * i;
        painter->setPen(QPen(Qt::black, 8 - sw * i * 100,
                        Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->drawPoint(path.pointAtPercent(i));
    }
    //    painter->fillPath(path, Qt::black);
}

void MyItem::drawPatchPath3(QPointF &p1, QPointF &p2, QPainterPath &path, qreal &pw, qreal &cw)
{
    qreal sw = (pw - cw) / 100.;
    int k = 0;
    for (qreal i = 0; i <= 1; i += 0.01) {
        k++;
        painter->setPen(QPen(Qt::black, pw - cw * i * 100,
                             Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->drawPoint(path.pointAtPercent(i));
    }
}

void MyItem::drawPath()
{
    qDebug() << "points length" << points.length();
    if (points.isEmpty()) {
        return;
    }
    QPointF first = points.first();
    if (points.length() <= 2) {
        painter->setPen(QPen(Qt::red, 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->setRenderHints(QPainter::Antialiasing);
        painter->drawPoint(first);
        update();
        return;
    }
    QPainterPath path;
    path.moveTo(first);
    qreal pw = 6;
    for (int i = 1; i < points.length(); i ++) {
        QPointF lp = points[i - 1];
        QPointF p = points[i];
        QPointF centerP = (lp + p) / 2;
        path.quadTo(lp, centerP);


        painter->setPen(QPen(Qt::red, qMax(i % 6, 2), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->setRenderHints(QPainter::Antialiasing);
        painter->drawPath(path);
        qreal cw = qMax(i % 6, 2);
//        drawPatchPath3(lp, centerP, path, pw, cw);
//        painter->fillPath(strokePath(10, path), Qt::red);
        update();
        pw = cw;

        QPointF cp = path.currentPosition();
        path &= QPainterPath();
        path.moveTo(cp);
    }
}

QPainterPath MyItem::strokePath(qreal width, QPainterPath &p)
{
    QPainterPathStroker stroker;
    stroker.setWidth(width);
    stroker.setCapStyle(Qt::RoundCap);
    stroker.setJoinStyle(Qt::RoundJoin);
    return stroker.createStroke(p);
}
