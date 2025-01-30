#include "server.h"
#include <iostream>
#include <QJsonArray>

using namespace std;

Server::Server(Model& model, QObject *parent) : model(model), QObject(parent) {
    server = new QTcpServer(this);
    int port = 1234;
    if (server->listen(QHostAddress::Any, port)) {
        cout << "Server started on port " << port << "..." << endl;
        connect(server, &QTcpServer::newConnection, this, &Server::onNewConnection);
    } else {
        cout << "Server failed to start!";
    }
}

void Server::onNewConnection() {
    QTcpSocket *clientSocket = server->nextPendingConnection();
    cout << "New client connected:" << clientSocket->peerAddress().toString().toStdString() << endl;

    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::onReadyRead);
}

void Server::onReadyRead() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (clientSocket) {
        QByteArray requestData = clientSocket->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(requestData);

        if (!jsonDoc.isNull()) {
            QJsonObject jsonObj = jsonDoc.object();
            QByteArray jsonResponse = QJsonDocument(jsonObj).toJson(QJsonDocument::Indented);

            cout << "Parsed JSON: " << jsonResponse.constData() << endl;
            map<string, ValueType> map;
            map["status"] = 200;
            map["table"] = model.getTable();
            QJsonObject response = getJsonObject(map);
            sendResponse(clientSocket, response);
        } else {
            cout << "Invalid JSON format!"  << endl;
        }
    }
}

QJsonObject Server::getJsonObject(map<string, ValueType>& map) {
    QJsonObject responseObj;
    for (const auto& pair : map) {
        responseObj[QString::fromStdString(pair.first)] = variantToJsonValue(pair.second);
    }
    return responseObj;
}

QJsonValue Server::variantToJsonValue(const ValueType& value) {
    if (holds_alternative<int>(value)) {
        return QJsonValue(get<int>(value));
    } else if (holds_alternative<QString>(value)) {
        return QJsonValue(get<QString>(value));
    } else if (holds_alternative<RequestType>(value)) {
        RequestType requestType = get<RequestType>(value);
        switch (requestType) {
        case RequestType::SET:
            return QJsonValue("SET");
        case RequestType::GET:
            return QJsonValue("GET");
        default:
            return QJsonValue();
        }
    } else if (holds_alternative<reference_wrapper<const vector<vector<bool>>>>(value)) {
        const auto& table = get<reference_wrapper<const vector<vector<bool>>>>(value).get();
        QJsonArray tableArray;
        for (const auto& row : table) {
            QJsonArray rowArray;
            for (bool cell : row) {
                rowArray.append(QJsonValue(cell));
            }
            tableArray.append(rowArray);
        }
        return tableArray;
    }
    //cout << "Nothing found" << endl;
    return QJsonValue();
}


void Server::sendResponse(QTcpSocket *clientSocket, QJsonObject& responseObj) {
    QJsonDocument responseDoc(responseObj);
    QByteArray responseData = responseDoc.toJson();

    //QByteArray jsonResponse = responseDoc.toJson(QJsonDocument::Indented);
    //cout << "Sending JSON: " << jsonResponse.constData() << endl;

    if (clientSocket->state() == QAbstractSocket::ConnectedState) {
        clientSocket->write(responseData);
        clientSocket->flush();
    } else {
        cout << "Socket is not connected!" << endl;
    }
}
