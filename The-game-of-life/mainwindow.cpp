#include "mainwindow.h"
#include <QWidget>
#include <QDebug>
#include <QLineEdit>
#include <QLabel>
#include <QIntValidator> // Ajouter cet include pour QIntValidator
#include "local/mainwindow_local.h"
#include "online/mainwindow_online.h"
#include "online/network/client.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    radioLocal = new QRadioButton("Play in local", this);
    radioOnline = new QRadioButton("Play online", this);

    startButton = new QPushButton("Start game", this);

    // Initialisation des composants communs
    setupCommonComponents();

    // Initialisation du mode local
    setupLocalMode();

    // Initialisation du mode en ligne
    setupOnlineMode();

    connect(startButton, &QPushButton::clicked, this, &MainWindow::launchGame);
    connect(radioLocal, &QRadioButton::toggled, this, &MainWindow::toggleLocalInputs);
    connect(radioOnline, &QRadioButton::toggled, this, &MainWindow::toggleOnlineInputs);

    layout = new QVBoxLayout;
    layout->addWidget(radioLocal);
    layout->addWidget(radioOnline);
    layout->addWidget(ipLabel);
    layout->addWidget(ipInput);
    layout->addWidget(portLabel);
    layout->addWidget(portInput);
    layout->addWidget(widthLabel);
    layout->addWidget(widthInput);
    layout->addWidget(heightLabel);
    layout->addWidget(heightInput);
    layout->addWidget(startButton);

    centralWidget->setLayout(layout);

    resize(300, 250);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupCommonComponents()
{
    ipLabel = new QLabel("IP Address:", this);
    ipInput = new QLineEdit(this);
    ipInput->setPlaceholderText("127.0.0.1");
    ipInput->setText("127.0.0.1");

    portLabel = new QLabel("Port:", this);
    portInput = new QLineEdit(this);
    portInput->setPlaceholderText("1234");
    portInput->setText("1234");

    widthLabel = new QLabel("Width:", this);
    widthInput = new QLineEdit(this);
    widthInput->setText("100");

    heightLabel = new QLabel("Height:", this);
    heightInput = new QLineEdit(this);
    heightInput->setText("100");

    QIntValidator *intValidator = new QIntValidator(1, 9999, this);
    portInput->setValidator(intValidator);
    widthInput->setValidator(intValidator);
    heightInput->setValidator(intValidator);
}

void MainWindow::setupLocalMode()
{
    widthLabel->setVisible(false);
    widthInput->setVisible(false);
    heightLabel->setVisible(false);
    heightInput->setVisible(false);
}

void MainWindow::setupOnlineMode()
{
    ipLabel->setVisible(false);
    ipInput->setVisible(false);
    portLabel->setVisible(false);
    portInput->setVisible(false);
}

void MainWindow::launchGame()
{
    if (radioLocal->isChecked()) {
        qDebug() << "Starting in local mode..";
        QString widthText = widthInput->text();
        QString heightText = heightInput->text();

        if(widthText == "" || heightText == "") {
            qDebug() << "One or more input are not entered";
        } else {
            int width = widthText.toInt();
            int height = heightText.toInt();

            static MainWindowLocal w(width, height);
            w.show();
            this->close();
        }
    } else if (radioOnline->isChecked()) {
        qDebug() << "Starting in online mode...";
        QString ipText = ipInput->text();
        QString portText = portInput->text();

        if(ipText == "" || portText == "") {
            qDebug() << "One or more input are not entered";
        } else {
            Client client;
            int port = portText.toInt();
            client.connectToServer(ipText, port);
            if(client.isConnected()) {
                qDebug() << "You are connected to the server";
            } else {
                qDebug() << "You are not connected to the server";
            }
            static MainWindowOnline w;
            w.show();
            this->close();
        }
    } else {
        qDebug() << "Please select a game mode";
    }
}

void MainWindow::toggleOnlineInputs(bool checked)
{
    ipLabel->setVisible(checked);
    ipInput->setVisible(checked);
    portLabel->setVisible(checked);
    portInput->setVisible(checked);
}

void MainWindow::toggleLocalInputs(bool checked)
{
    widthLabel->setVisible(checked);
    widthInput->setVisible(checked);
    heightLabel->setVisible(checked);
    heightInput->setVisible(checked);
}
