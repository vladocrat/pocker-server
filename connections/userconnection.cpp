#include "userconnection.h"

#include <QDataStream>
#include <QByteArray>

#include "controllers/usercontroller.h"
#include "protocol.h"

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
    case Protocol::Client::CL_CREATE_ROOM: {

        break;
    }
    case Protocol::Client::CL_ROOM_CHOICE:
    {
        int roomId = -1;
        stream >> roomId;
        emit roomChosen(roomId);
        break;
    }
    case Protocol::Client::CL_LEAVE_ROOM:
    {
        emit roomLeft();
    }
    default:
    {
        qDebug() << "wrong command";
        qDebug() << command;
        break;
    }
    }
}



