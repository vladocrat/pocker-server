#include "pendingconnection.h"

#include <QDataStream>

#include "protocol.h"
#include "LoginData.h"
#include "RegisterData.h"
#include "Message.h"
#include "userrepository.h"
#include "server.h"

namespace Internal
{
LoginData readClientData(QDataStream& stream)
{
    QByteArray arr;
    stream >> arr;
    QDataStream readLoginData(arr);
    QString login;
    QString password;
    readLoginData >> login;
    readLoginData >> password;
    LoginData data;
    data.login = login;
    data.password = password;

    return data;
}

RegisterData readRegisterData(QDataStream& stream)
{
    QByteArray arr;
    stream >> arr;
    QDataStream readRegisterData(arr);
    QString login;
    QString password;
    QString email;
    readRegisterData >> login;
    readRegisterData >> password;
    readRegisterData >> email;

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
            msg.text = "Failed to login";
            qDebug() << msg.text;

            if (!send(Protocol::Errors::SV_LOGIN_ERR, msg.serialise())) {
                qDebug() << "failed to send";
            }

            socket()->close();

            return;
        }

        qDebug() << profile.toString();
        emit logged(profile);
        break;
    }

    case Protocol::Client::CL_REGISTER: {
        auto registerData = Internal::readRegisterData(stream);

        if (!UserRepository::instance()->registerUser(registerData)) {

            Message msg;
            msg.text = "Failed to register";
            if (!send(Protocol::Errors::SV_REGISTRATION_ERR, msg.serialise())) {
                qDebug() << "failed to send";
            }

            socket()->close();

            return;
        }

        if (!sendCommand(Protocol::Server::SV_REGISTER)) {
            qDebug() << "failed to send";
            socket()->close();
        }

        break;
    }

    default:
        qDebug() << "Incorrect command";
        socket()->close();

        return;
    }
}




