#ifndef MAINWINDOW_LOCAL_H
#define MAINWINDOW_LOCAL_H

#include <QMainWindow>
#include <QTableWidget>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QTimer>

#include "model/model.h"
#include "view/tableWidget.h"

class MainWindowLocal : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowLocal(int rows = 100, int cols = 100, QWidget *parent = nullptr);
    ~MainWindowLocal();

private:
    QTableWidget *tableWidget;
    Model model;
    TableWidget *widget = nullptr;
    QTimer *timer;
    bool running;

    void update_game();
    void toggle_game();
    void draw_table();
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // MAINWINDOW_LOCAL_H
