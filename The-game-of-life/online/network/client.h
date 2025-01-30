#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
class Client : public QObject {
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);
    void connectToServer(QString ip, int port);
    void sendData(const QString &message);
    void onReadyRead();
    const QTcpSocket* getSocket() const;
    bool isConnected();
private:
    QTcpSocket *socket;
    QByteArray responseBuffer;
};

#endif // CLIENT_H
