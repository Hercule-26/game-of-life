#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>
#include "../model/model.h"

class TableWidget : public QGraphicsView {
    Q_OBJECT

public:
    explicit TableWidget(QWidget *parent = nullptr, int cellSize = 20, Model* model = nullptr);
    void refreshGrid();
protected:
    void wheelEvent(QWheelEvent *event) override;

private:
    QGraphicsScene *scene;
    int cellSize;
    double scaleFactor = 1.15;
    Model* model;

    void createGrid();
};

#endif // TABLEWIDGET_H
