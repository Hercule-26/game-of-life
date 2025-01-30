#include <QCoreApplication>
#include "client.h"
#include <QLoggingCategory>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    Client client;
    client.connectToServer();
    client.sendData("Hello, server!");
    return a.exec();
}
