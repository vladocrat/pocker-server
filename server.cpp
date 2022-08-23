#include <QtCore>
#include <QTcpSocket>
#include <QDebug>
#include <QString>
#include <iostream>

#include "server.h"
#include "controllers/usercontroller.h"
#include "protocol.h"

Server::Server()
{

}

Server::~Server()
{
    for (auto pendingConnection: qAsConst(m_pendingConnections)) {
        if (pendingConnection->socket()) {
            pendingConnection->socket()->close();
        }
    }
}

void Server::listen()
{
    if (!QTcpServer::listen(m_address, m_port)) {
        qDebug() << "bad settings";

        return;
    }

    qDebug() << "server listening on: " << m_address << " " << m_port;
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    auto pendingConnection = new PendingConnection;
    pendingConnection->socket()->setSocketDescriptor(socketDescriptor);

    connect(pendingConnection->socket(), &QTcpSocket::disconnected, [this, pendingConnection] () {
        m_pendingConnections.removeOne(pendingConnection);
    });

    m_pendingConnections.push_back(pendingConnection);
}

void Server::authorised(const Profile& profile)
{
    auto pendingConnection = static_cast<PendingConnection*>(sender());

    if (UserController::instance()->findUserByName(profile.name)) {

        if (!pendingConnection->sendCommand(Protocol::Errors::SV_ALREADY_LOGED_ERR)) {
            qDebug() << "failed to send";
        }

        qDebug() << "user is already logged in";
        pendingConnection->socket()->close();
        pendingConnection->deleteLater();

        return;
    }

    m_pendingConnections.removeOne(pendingConnection);
    auto userConnection = new UserConnection;
    userConnection->setScoket(pendingConnection->clearSocket());
    userConnection->init();
    auto user = new User(userConnection);
    user->setProfile(profile);

    if (!userConnection->send(Protocol::Server::SV_LOGIN, user->serialize())) {
        qDebug() << "failed to send";
        userConnection->socket()->close();
        userConnection->deleteLater();
    }

    if (!userConnection->send(Protocol::Server::SV_LIST_OF_ROOMS,
                              UserController::instance()->serialiseRooms())) {
        qDebug() << "failed to send";
        userConnection->socket()->close();
        userConnection->deleteLater();
    }

    UserController::instance()->addUser(user);
}

void Server::setAddress(const QHostAddress &address)
{
    m_address = address;
}

void Server::setAddress(const QString &address)
{
    QHostAddress hostAddress(address);
    m_address = hostAddress;
}

void Server::setPort(int port)
{
    m_port = port;
}

QHostAddress Server::address()
{
    return m_address;
}

int Server::port()
{
    return m_port;
}
