#include "client.h"
#include <QEventLoop>
#include <QThread>
#include <iostream>

using namespace std;

Client::Client(QObject *parent) : QObject(parent) {    
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, []() {
        cout << "Disconnected from server" << endl;
    });

    connect(socket, &QTcpSocket::errorOccurred, this, [](QAbstractSocket::SocketError socketError) {
        cout << "Erreur with socket : " << socketError << endl;
    });

}

void Client::connectToServer() {
    socket->connectToHost("127.0.0.1", 1234);

    if (socket->waitForConnected(3000)) {
        cout << "Connected to server!" << endl;
    } else {
        cout << "Connection failed!" << endl;
    }
}

void Client::sendData(const QString &message) {
    if (socket->state() == QAbstractSocket::ConnectedState) {
        QJsonObject jsonObj;
        jsonObj["command"] = "sendData";
        jsonObj["data"] = message;
        QJsonDocument jsonDoc(jsonObj);
        QByteArray jsonData = jsonDoc.toJson();

        socket->write(jsonData);
        socket->flush();

        QEventLoop loop;
        connect(socket, &QTcpSocket::readyRead, &loop, &QEventLoop::quit);
        loop.exec();

    } else {
        cout << "Not connected to server!" << endl;
    }
}

void Client::onReadyRead() {
    QByteArray responseData = socket->readAll();
    responseBuffer.append(responseData);

    QJsonDocument responseDoc = QJsonDocument::fromJson(responseBuffer);

    if (!responseDoc.isNull()) {
        QJsonObject responseObj = responseDoc.object();
        QByteArray jsonResponse = QJsonDocument(responseObj).toJson(QJsonDocument::Indented);

        cout << "Response from server: " << jsonResponse.constData() << endl;

        responseBuffer.clear();
    } else {
        cout << "Waiting for more data..." << endl;
    }
}

