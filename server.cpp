#include <QtCore>
#include <QTcpSocket>
#include <QDebug>

#include "server.h"
#include "room.h"

Server::Server(Room* room, QObject* parent)
{
    m_room = room;
    initServer();
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::newUser);
}

Server::~Server()
{
    tcpServer->close();
    for (auto& x : users) {
        x->deleteLater();
    }
    tcpServer->deleteLater();
}

void Server::initServer()
{
    tcpServer = new QTcpServer(this);
    QHostAddress address("127.0.0.1");
    if (!tcpServer->listen(address, 7890)) {
        return;
    }
    qDebug() << "server started";
}

void Server::newUser()
{
    qDebug() << Q_FUNC_INFO;
    QTcpSocket* clientConnection = tcpServer->nextPendingConnection();

    User* user = new User();

    user->setSocket(clientConnection);
    users.append(user);

    Player* player = static_cast<Player*>(user);
    m_room->setPlayer(player);

    connect(user, &User::onUserConnectionLost, this, &Server::onConnectionLost);

    emit user->onUserConnected();
}

void Server::onConnectionLost(User* user)
{
    int usersRemoved = users.removeAll(user);
    if (usersRemoved > 1 || usersRemoved == 0) {
        qDebug() << "faild to disconnect user";
    }

}

