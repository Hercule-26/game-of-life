#include "mainwindow_online.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

MainWindowOnline::MainWindowOnline(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QLabel *label = new QLabel("Mode Online", this);
    layout->addWidget(label);

    QPushButton *button = new QPushButton("Click Me", this);
    layout->addWidget(button);

    connect(button, &QPushButton::clicked, this, []() {
        qDebug() << "Button clicked in Online mode!";
    });

    resize(600, 600);
}

MainWindowOnline::~MainWindowOnline()
{
}
