#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QKeyEvent>
#include <qgraphicsview.h>
#include <QTimer>

#include "model/model.h"
#include "view/tableWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int rows = 100, int cols = 100, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
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

#endif // MAINWINDOW_H
