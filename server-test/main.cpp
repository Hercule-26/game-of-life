#include <QCoreApplication>
#include "server.h"
#include "model/model.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    static Model model(100, 100);

    Server server(model);
    return a.exec();
}

