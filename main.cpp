#include <QCoreApplication>

#include "server.h"
#include "gamelogic.h"
#include "room.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    int retval;
    {
        Server::instance()->setAddress("127.0.0.1");
        Server::instance()->setPort(8082);
        Server::instance()->listen();
        retval = app.exec();
    }

    return retval;
}
