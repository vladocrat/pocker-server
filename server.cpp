#include <QtCore>
#include <QTcpSocket>
#include <QDebug>
#include <QDataStream>
#include <QString>

#include "server.h"
#include "room.h"
#include "protocol.h"
#include "LoginData.h"
#include "RegisterData.h"
#include "userrepository.h"
#include "usercontroller.h"
#include "Message.h"

namespace Internal
{

LoginData readClientData(QDataStream& stream)
{
    QString login;
    QString password;
    stream >> login;
    stream >> password;
    LoginData data;
    data.login = login;
    data.password = password;

    return data;
}

RegisterData readRegisterData(QDataStream& stream)
{
    QString login;
    QString password;
    QString email;
    stream >> login;
    stream >> password;
    stream >> email;

    RegisterData data;
    data.login = login;
    data.password = password;
    data.email = email;

    return data;
}

int readCommand(QDataStream& stream)
{
    int command = 0;
    stream >> command;

    return command;
}

bool sendCommand(QTcpSocket* socket, int command)
{
    if (socket->state() != QTcpSocket::ConnectedState) {
        qDebug() << "socket not connected";

        return false;
    }

    QByteArray msg;
    QDataStream stream(&msg, QIODevice::WriteOnly);
    QDataStream socketStream(socket);
    stream << command;
    socketStream << msg.size() << msg;
    socket->flush();

    return true;
}

bool send(QTcpSocket* socket, int command, const QByteArray& data)
{
    if (socket->state() != QTcpSocket::ConnectedState) {
        qDebug() << "socket not connected";

        return false;
    }

    QByteArray msg;
    QDataStream stream(&msg, QIODevice::WriteOnly);
    QDataStream socketStream(socket);
    stream << command << data;
    socketStream << msg.size() << msg;
    socket->flush();

    return true;
}

};

Server::Server(QHostAddress address, int port)
{
    if (!listen(address, port)) {
        qDebug() << "bad settings";
        return;
    }
    qDebug() << "server listening on: " << address << " " <<port;
}

Server::~Server()
{
    for (auto& socket: m_pendingConnections) {
        socket->close();
    }
}


void Server::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket* socket = new QTcpSocket;

    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, &QTcpSocket::readyRead, [this, socket] () {
        QDataStream another(socket);

        if ((socket->bytesAvailable() >= sizeof(int)) && this->m_packageSize == -1) {
            another >> this->m_packageSize;
        } else {
            return;
        }

        if (socket->bytesAvailable() < this->m_packageSize) {
            return;
        }

        QByteArray data;
        another >> data;
        this->m_packageSize = -1;
        handleData(socket, data);
    });

    // void handle disconnect
    connect(socket, &QTcpSocket::disconnected, [this, socket] () {
        m_pendingConnections.removeOne(socket);
        socket->deleteLater();
    });

    m_pendingConnections.push_back(socket);
}

void Server::handleData(QTcpSocket* socket, const QByteArray& data)
{
    QDataStream stream(data);
    int command = Internal::readCommand(stream);

    switch (command) {
    case Protocol::Client::CL_HELLO: {
        Internal::sendCommand(socket, Protocol::Server::SV_HELLO);

        return;
    }

    case Protocol::Client::CL_LOGIN: {
        auto loginData = Internal::readClientData(stream);

        qDebug() << loginData.login << " " << loginData.password;

        User user(socket);
        if (!UserRepository::instance()->login(loginData, user)) {
            Message msg;
            msg.msg = "failed to login";
            qDebug() << msg.msg;
            Internal::send(socket, Protocol::Errors::SV_LOGIN_ERR, msg.serialize());
            socket->close();

            return;
        }

        if (!UserController::instance()->addUser(user)) {
            command = Protocol::Errors::SV_LOGIN_ERR;
        } else {
            command = Protocol::Server::SV_LOGIN;
        }

        qDebug() << user.toString();

        Internal::send(socket, command, user.serialize());
        break;
    }

    case Protocol::Client::CL_REGISTER: {
        auto registerData = Internal::readRegisterData(stream);

        Message msg;
        if (!UserRepository::instance()->registerUser(registerData)) {
            msg.msg = "failed to register";
            qDebug() << msg.msg;
            Internal::send(socket, Protocol::Errors::SV_REGISTRATION_ERR, msg.serialize());
            socket->close();

            return;
        }

        Internal::send(socket, Protocol::Server::SV_REGISTER, msg.serialize());
        break;
    }

    default:
        qDebug() << "Incorrect command";
        socket->close();

        return;
    }
}


