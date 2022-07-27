#include "userconnection.h"

#include <QDataStream>
#include <QByteArray>

#include "controllers/usercontroller.h"
#include "integer.h"
#include "protocol.h"
#include "room.h"

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
    case Protocol::Client::CL_CREATE_ROOM:
    {
        //TODO join room on creation
        QByteArray roomData;
        stream >> roomData;
        auto room = new Lobby(Room::deserialise(roomData));
        UserController::instance()->addRoom(room);

        if (!send(Protocol::Server::SV_ROOM_CREATED, Room::serialise(*room))) {
            qDebug() << "failed to send";
            socket()->close();
        }

        break;
    }
    case Protocol::Client::CL_ROOM_CHOICE:
    {
        QByteArray arr;
        stream >> arr;
        emit roomChosen(Integer::deserealise(arr).val);
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
        socket()->close();
        break;
    }
    }
}



