#include "server.h"
#include <sstream>
#include <string>

using namespace std;
Server::Server(Model& model) : model(model) {
    server = new QTcpServer(this);

    connect(server, &QTcpServer::newConnection, this, &Server::onNewConnection);

    if (!server->listen(QHostAddress::Any, 1234)) {
        qDebug() << "Server could not start!";
    } else {
        qDebug() << "Server started on port 1234";
    }
}

void Server::onNewConnection() {
    QTcpSocket *clientSocket = server->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::onReadyRead);
    qDebug() << "New client connected!";
}

void Server::onReadyRead() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    QByteArray data = clientSocket->readAll();
    qDebug() << "Received data: " << data;

    vector<string> splited_command = split(data.toStdString(), ' ');
    string first = splited_command.at(0);
    if(first.compare("set")) {
        if(splited_command.size() != 4) {
            clientSocket->write("Arguments invalid !");
        }
        try {
            int x = stoi(splited_command.at(1));
            int y = stoi(splited_command.at(2));
            bool value = stoi(splited_command.at(3));
            model.set(x, y, value);
        } catch (...) {
            clientSocket->write("Error while parsing !");
        }
    } else if (first.compare("get")) {
        if(splited_command.size() != 3) {
            clientSocket->write("Arguments invalid !");
        }
        try {
            int x = stoi(splited_command.at(1));
            int y = stoi(splited_command.at(2));
            int value = model.get_at(x, y);
            string result = "get " + to_string(value);

            clientSocket->write(QByteArray::fromStdString(result));
        } catch (...) {
            clientSocket->write("Error while parsing !");
        }
    }
}

void Server::sendData(QTcpSocket *clientSocket, bool response) {
    clientSocket->write("Hello from server!");
}

vector<string> Server::split(const string& str, char delimiter) {
    vector<string> result;
    string token;
    stringstream ss(str);

    while (getline(ss, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}


