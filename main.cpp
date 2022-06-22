#include <QCoreApplication>

#include "server.h"
#include "gamelogic.h"
#include "room.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Server server(QHostAddress("127.0.0.1"), 8082);
    return app.exec();
}
