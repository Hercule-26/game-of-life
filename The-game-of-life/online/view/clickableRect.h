#ifndef CLICKABLERECTONLINE_H
#define CLICKABLERECTONLINE_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsSceneMouseEvent>

class ClickableRect : public QObject, public QGraphicsRectItem {
    Q_OBJECT

public:
    explicit ClickableRect(const QRectF &rect, QGraphicsItem *parent = nullptr);

signals:
    void clicked();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // CLICKABLERECT_H
