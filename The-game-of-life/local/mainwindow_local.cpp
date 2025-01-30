#include "mainwindow_local.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QDebug>

MainWindowLocal::MainWindowLocal(int rows, int cols, QWidget *parent)
    : QMainWindow(parent), model(rows, cols), running(false)
{
    widget = new TableWidget(parent, 10, &model);
    setCentralWidget(widget);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindowLocal::update_game);

    connect(&model, &Model::tableUpdated, widget, &TableWidget::refreshGrid);

    resize(600, 600);
}

MainWindowLocal::~MainWindowLocal()
{
    delete timer;
}

void MainWindowLocal::toggle_game()
{
    if (running) {
        timer->stop();
        running = false;
    } else {
        timer->start(0);
        running = true;
    }
}

void MainWindowLocal::update_game()
{
    model.run_life();
    update();
}

void MainWindowLocal::draw_table()
{
    QPainter painter(this);
    int cellSize = 10;

    for (int i = 0; i < model.get_table_rows(); ++i) {
        for (int j = 0; j < model.get_table_cols(); ++j) {
            QRect cellRect(j * cellSize, i * cellSize, cellSize, cellSize);
            if (model.get_at(i, j) == 1) {
                painter.fillRect(cellRect, Qt::black);
            } else {
                painter.fillRect(cellRect, Qt::white);
            }
            painter.drawRect(cellRect);
        }
    }
}

void MainWindowLocal::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space) {
        toggle_game();
        //qDebug() << "Touche Espace enfoncée !";
    }
}
