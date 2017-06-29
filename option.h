#ifndef OPTION_H
#define OPTION_H
#include "QGraphicsRectItem"
#include "QGraphicsSceneMouseEvent"
#include "QObject"
#include "QPropertyAnimation"

class option:public QObject,public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
    Q_PROPERTY(qreal scale READ scale WRITE setScale)
private:
    QGraphicsTextItem *text;
    QPropertyAnimation *anim1,*anim2;
public:
    option(QString t);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
    void clicked();
};

#endif // OPTION_H
