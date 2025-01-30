#include "clickableRect.h"
#include <QGraphicsSceneMouseEvent>

ClickableRect::ClickableRect(const QRectF &rect, QGraphicsItem *parent)
    : QObject(), QGraphicsRectItem(rect, parent) {}

void ClickableRect::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit clicked();
    QGraphicsRectItem::mousePressEvent(event);
}
