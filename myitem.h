#ifndef MYITEM_H
#define MYITEM_H

#include <QGraphicsObject>
#include <QGraphicsItem>
#include <QPainter>

struct PointInfo {
    qreal x;
    qreal y;
    qreal w;
};

class MyItem : public QGraphicsObject
{
    Q_OBJECT
public:
    MyItem(QRectF rect);
    ~MyItem() override;
    void drawPress(const QPointF &point);
    void drawMove(const QPointF &lp, const QPointF &p);
    void drawRelease(const QPointF &p);

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    void initCanvas();
    void drawPatchPath(QPointF p1, QPointF p2);
    void drawPatchPath2(QPointF p1, QPointF p2);
    void drawPatchPath3(QPointF &p1, QPointF &p2, QPainterPath &path, qreal &pw, qreal &cw);
    void drawPath();
    QPainterPath strokePath(qreal width, QPainterPath &p);


private:
    QSizeF size;
    QImage *canvas;
    QPainter *painter;
    QList<QPointF> points;
};

#endif // MYITEM_H
