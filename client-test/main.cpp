#include <QCoreApplication>
#include <QTcpSocket>
#include <QDebug>

QTcpSocket *socket;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    socket = new QTcpSocket();
    qDebug() << "Attempting to connect to the server...";

    socket->connectToHost("127.0.0.1", 1234);  // Adresse et port du serveur

    if (!socket->waitForConnected()) {
        qDebug() << "Connection failed!";
        return 1;  // Exit if the connection fails
    } else {
        qDebug() << "Connected to the server!";
    }

    // Envoi de la requête "get 0 1"
    socket->write("get 0 1");
    socket->flush();
    qDebug() << "Request sent: get 0 1";

    // Attente de la réponse du serveur
    if (socket->waitForReadyRead(5000)) {  // Attendre 5 secondes maximum pour la réponse
        QByteArray response = socket->readAll();
        qDebug() << "Server response: " << response;
    } else {
        qDebug() << "No response from server within the timeout.";
    }

    socket->close();

    return a.exec();
}
