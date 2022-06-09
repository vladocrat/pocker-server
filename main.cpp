#include <QCoreApplication>

#include "server.h"
#include "gamelogic.h"
#include "room.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Room room;
    Server server(&room); // is this a correct way? pepega
    GameLogic logic;
    return app.exec();
}
