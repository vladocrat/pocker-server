#include "pendingconnection.h"

#include <QDataStream>

#include "protocol.h"
#include "LoginData.h"
#include "RegisterData.h"
#include "Message.h"
#include "userrepository.h"
#include "controllers/usercontroller.h"
#include "server.h"

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

};

PendingConnection::PendingConnection()
{
    connect(this, &PendingConnection::logged, Server::instance(), &Server::authorised);
    connect(socket(), &QTcpSocket::readyRead, this, &PendingConnection::handleData);
}

void PendingConnection::handleData()
{
    QByteArray data;
    readUserData(data);
    QDataStream stream(data);
    int command = readCommand(stream);

    switch (command) {
    case Protocol::Client::CL_HELLO: {

        qDebug() << "pending connection hello";

        if (!sendCommand(Protocol::Server::SV_HELLO)) {
            qDebug() << "failed to send";
        }

        return;
    }

    case Protocol::Client::CL_LOGIN: {
        auto loginData = Internal::readClientData(stream);
        Profile profile;

        qDebug() << loginData.login << " " << loginData.password;

        if (!UserRepository::instance()->login(loginData, profile)) {
            Message msg;
            msg.text = "failed to login";
            qDebug() << msg.text;

            if (!send(Protocol::Errors::SV_LOGIN_ERR, msg.serialise())) {
                qDebug() << "failed to send";
            }

            socket()->close();

            return;
        }

        //TODO return list of rooms on success
        qDebug() << profile.toString();
        emit logged(profile);
        break;
    }

    case Protocol::Client::CL_REGISTER: {
        auto registerData = Internal::readRegisterData(stream);

        Message msg;

        if (!UserRepository::instance()->registerUser(registerData)) {
            msg.text = "failed to register";
            qDebug() << msg.text;

            if (!send(Protocol::Errors::SV_REGISTRATION_ERR, msg.serialise())) {
                qDebug() << "failed to send";
            }

            socket()->close();

            return;
        }

        msg.text = "registered";

        if (!send(Protocol::Server::SV_REGISTER, msg.serialise())) {
            qDebug() << "failed to send";
        }

        break;
    }

    default:
        qDebug() << "Incorrect command";
        socket()->close();

        return;
    }
}




