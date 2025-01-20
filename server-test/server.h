#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include "model/model.h"

class Server : public QObject
{
public:
    Server(Model& model);

    void onNewConnection();
    void onReadyRead();

    void sendData(QTcpSocket *clientSocket, bool response);
    void setData();
    std::vector<std::string> split(const std::string& str, char delimiter);

private:
    QTcpServer *server;
    Model& model;
};

#endif // SERVER_H
