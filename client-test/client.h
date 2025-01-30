#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>

class Client : public QObject {
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);
    void connectToServer();
    void sendData(const QString &message);
    void onReadyRead();

private:
    QTcpSocket *socket;
    QByteArray responseBuffer;
};

#endif // CLIENT_H
