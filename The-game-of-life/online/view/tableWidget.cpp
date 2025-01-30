#include "tableWidget.h"
#include "clickableRect.h"
#include <QBrush>
#include <QPen>
#include "ClickableRect.h"

TableWidget::TableWidget(QWidget *parent, int cellSize)
    : QGraphicsView(parent), cellSize(cellSize) {
    scene = new QGraphicsScene(this);
    setScene(scene);
    setRenderHint(QPainter::Antialiasing);
    createGrid();
}

void TableWidget::createGrid() {
    /*
    for (int row = 0; row < model->get_table_rows(); ++row) {
        for (int col = 0; col < model->get_table_cols(); ++col) {
            auto *rect = new ClickableRect(QRectF(col * cellSize, row * cellSize, cellSize, cellSize));
            rect->setBrush(Qt::white);
            rect->setPen(QPen(Qt::black));
            connect(rect, &ClickableRect::clicked, this, [this, rect, row, col]() {
                if (rect->brush() == Qt::white) {
                    rect->setBrush(Qt::black);
                    model->set(row, col, true);
                } else {
                    rect->setBrush(Qt::white);
                    model->set(row, col, false);
                }
                //qDebug() << model->get_at(row, col);
            });
            scene->addItem(rect);
        }
    }
    setSceneRect(0, 0, model->get_table_cols() * cellSize, model->get_table_rows() * cellSize);
    */
}

void TableWidget::wheelEvent(QWheelEvent *event) {
    if (event->modifiers() & Qt::ControlModifier) {
        if (event->angleDelta().y() > 0) {
            scale(scaleFactor, scaleFactor);
        } else {
            scale(1 / scaleFactor, 1 / scaleFactor);
        }
    } else {
        QGraphicsView::wheelEvent(event);
    }
}

void TableWidget::refreshGrid() {
    /*
    for (int row = 0; row < model->get_table_rows(); ++row) {
        for (int col = 0; col < model->get_table_cols(); ++col) {
            QGraphicsItem *item = scene->itemAt(col * cellSize, row * cellSize, QTransform());
            if (item) {
                auto *rect = dynamic_cast<ClickableRect *>(item);
                if (rect) {
                    if (model->get_at(row, col)) {
                        rect->setBrush(Qt::black);
                    } else {
                        rect->setBrush(Qt::white);
                    }
                }
            }
        }
    }
    */
}
