#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <string>
#include "model/model.h"
#include "model/requestType.h"
using ValueType = std::variant<RequestType, int, QString, std::reference_wrapper<const std::vector<std::vector<bool>>>>;

class Server : public QObject {
    Q_OBJECT

public:
    explicit Server(Model& model, QObject *parent = nullptr);

private slots:
    void onNewConnection();
    void onReadyRead();
    void sendResponse(QTcpSocket *clientSocket, QJsonObject& responseObj);
    QJsonObject getJsonObject(std::map<std::string, ValueType>& map);
    QJsonValue variantToJsonValue(const ValueType& value);

private:
    QTcpServer *server;
    Model model;
};

#endif // SERVER_H
