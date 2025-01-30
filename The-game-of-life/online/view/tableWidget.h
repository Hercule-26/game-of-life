#ifndef TABLEWIDGETONLINE_H
#define TABLEWIDGETONLINE_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>

class TableWidget : public QGraphicsView {
    Q_OBJECT

public:
    explicit TableWidget(QWidget *parent = nullptr, int cellSize = 20);
    void refreshGrid();
protected:
    void wheelEvent(QWheelEvent *event) override;

private:
    QGraphicsScene *scene;
    int cellSize;
    double scaleFactor = 1.15;

    void createGrid();
};

#endif // TABLEWIDGET_H
