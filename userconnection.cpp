#include "userconnection.h"

#include <QDataStream>
#include <QByteArray>

#include "usercontroller.h"
#include "../common/protocol.h"

UserConnection::UserConnection()
{

}

void UserConnection::init()
{
    connect(socket(), &QTcpSocket::readyRead, this, &UserConnection::handleData);
}

void UserConnection::handleData()
{
    QByteArray data;
    readUserData(data);
    QDataStream stream(data);
    int command = readCommand(stream);

      //TODO handle data

    switch (command) {
    case Protocol::Client::CL_HELLO:
    {
        qDebug() << "hello from client";

        if (!sendCommand(Protocol::Server::SV_HELLO)) {
            qDebug() << "failed to send";
            socket()->close();
        }

        break;
    }
    default:
    {
        qDebug() << "wrong command";
        break;
    }
    }
}



