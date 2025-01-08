#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

class Server : public QObject
{
public:
    Server() {
        server = new QTcpServer(this);

        connect(server, &QTcpServer::newConnection, this, &Server::onNewConnection);

        if (!server->listen(QHostAddress::Any, 1234)) {
            qDebug() << "Server could not start!";
        } else {
            qDebug() << "Server started on port 1234";
        }
    }

    void onNewConnection() {
        QTcpSocket *clientSocket = server->nextPendingConnection();
        connect(clientSocket, &QTcpSocket::readyRead, this, &Server::onReadyRead);
        qDebug() << "New client connected!";
    }

    void onReadyRead() {
        QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
        QByteArray data = clientSocket->readAll();
        qDebug() << "Received data: " << data;
        clientSocket->write("Hello from server!");
    }

private:
    QTcpServer *server;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server server;
    return a.exec();
}
