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

namespace Internal
{
LoginData readClientData(QDataStream& stream)
{
    QString login;
    QString password;
    stream >> login;
    stream >> password;
    return LoginData {login, password};
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

};

Server::Server(QHostAddress address, int port)
{

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
        int packageSize = -1;
        QTcpSocket* client = static_cast<QTcpSocket*>(sender());
        QDataStream another(client);

        if ((client->bytesAvailable() >= sizeof(int)) && packageSize == -1) {
            another >> packageSize;
        } else {
            return;
        }

        if (client->bytesAvailable() < packageSize) {
            return;
        }

        QByteArray data;

        another >> data;
        packageSize = -1;
        m_pendingConnections.push_back(socket);
        handleData(data);
    });

    // void handle disconnect
    connect(socket, &QTcpSocket::disconnected, [this, socket] () {
        m_pendingConnections.removeOne(socket);
        socket->deleteLater();
    });

    m_pendingConnections.push_back(socket);
}

void Server::handleData(const QByteArray& data)
{
    QDataStream stream(data);
    int command = Internal::readCommand(stream);
    User user;

    switch (command) {
    case Protocol::Client::CL_HELLO: {
        QByteArray clientData;
        clientData.append(Protocol::Server::SV_HELLO);
         // TODO: propper write to BA
        //socket->write(clientData);
        return;
    }

    case Protocol::Client::CL_LOGIN: {
        auto loginData = Internal::readClientData(stream);


        if (!UserRepository::login(loginData, user)) {
            qDebug() << "failed to login";
            //socket->close(); // also notify user
            return;
        }

        if (!UserController::instance()->addUser(user)) {
            command = Protocol::Errors::SV_LOGIN_ERR;
        } else {
            command = Protocol::Server::SV_LOGIN;
        }

        QByteArray clientData;
        QDataStream clientStream(clientData);
        clientStream << command;
        //TODO overload for user;
        clientStream << user;
        //socket->write(clientData);
        break;
    }

    case Protocol::Client::CL_REGISTER: {
        auto registerData = Internal::readRegisterData(stream);
        User user;
        if (UserRepository::registerUser(registerData)) {
            UserController::instance()->addUser(user);
        } else {
           // socket->close();
        }

        break;
    }
    default:
        qDebug() << "Incorrect command";
        //socket->close();
        return;
    }
}


