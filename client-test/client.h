#ifndef CLIENT_H
#define CLIENT_H
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>
#include <iostream>
using namespace std;
class Client : public QObject
{
public:
    Client() {
        socket = new QTcpSocket(this);

        cout << "Attempting to connect to the server..." << endl;
        socket->connectToHost(QHostAddress::LocalHost, 1234);

        if (socket->waitForConnected(3000)) {  // Attente de la connexion (3 secondes)
            cout << "Connected to server!" << endl;
            connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
        } else {
            cout << "Connection failed! Error:" << socket->errorString().toStdString() << endl;
        }
    }

    void onReadyRead() {
        QByteArray data = socket->readAll();
        cout << "Received from server: " << data.toStdString()  << endl;
    }

private:
    QTcpSocket *socket;
};

#endif // CLIENT_H
