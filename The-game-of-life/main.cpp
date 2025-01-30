#include "mainwindow.h"
#include "online/network/client.h"
#include <QTcpSocket>
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Client client;
    client.connectToServer("127.0.0.1", 1234);
    //if(client.isConnected()) client.sendData("Hello, server!");
    w.show();
    return a.exec();
}
