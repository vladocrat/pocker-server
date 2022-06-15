#include <QDataStream>

#include "user.h"
#include "protocol.h"

User::User(const QString& login)
{
    m_login = login;
}

User::~User()
{
    m_socket->close();
    m_socket->deleteLater();
}

QTcpSocket* User::socket() const
{
    return m_socket;
}

QString User::login() const
{
    return m_login;
}

void User::setSocket(QTcpSocket* socket)
{
    m_socket = socket;
    //moved connects here coz for some reason was unable to do the following in a constructor
    //was complaining about this being nullptr
    //the guess is since the object wasn't created yet, there was no this...not sure though
    connect(m_socket, &QTcpSocket::readyRead, this, &User::readMessage);
    connect(m_socket, &QTcpSocket::disconnected, this, &User::onSocketDisconnected);
}

void User::readySend(int command, int money)
{
    writeMessage(command, money);
}

void User::readMessage()
{
    qDebug() << Q_FUNC_INFO;
    QTcpSocket* client = static_cast<QTcpSocket*>(sender());
    QDataStream another(client); //* reduce datastream scope

    if ((client->bytesAvailable() >= sizeof(int)) && m_packageSize == -1) {
        another >> m_packageSize;
    } else {
        return;
    }

    if (client->bytesAvailable() < m_packageSize) {
        return;
    }

    QByteArray array;
    another >> array;

    m_packageSize = -1;

    handleData(array);
}

void User::writeMessage(int command, int money)
{
    qDebug() << Q_FUNC_INFO;
    QByteArray msg;
    QDataStream stream(&msg, QIODevice::WriteOnly);
    QDataStream socketStream(m_socket);

    switch (command) {
    case CL_BET: {
        stream << CL_BET;
        stream << money;
        break;
    }
    case CL_FOLD: {
        stream << CL_FOLD;
        break;
    }
    case CL_RAISE: {
        stream << CL_RAISE;
        stream << money;
        break;
    }
    case CL_ALLIN: {
        stream << CL_ALLIN;
        break;
    }
    case CL_CALL: {
        stream << CL_CALL;
        break;
    }
    case CL_CHECK: {
        stream << CL_CHECK;
        break;
    }
    }
    socketStream << msg.size() << msg;
    m_socket->flush();
}

void User::onSocketDisconnected()
{
    m_socket->close();
    //TODO Dont need to delete socket, deleted automatically
    m_socket->deleteLater();
    emit onUserConnectionLost(this);
}

void User::handleData(const QByteArray& arr)
{
    qDebug() << Q_FUNC_INFO;
    QDataStream stream(arr);
    int command = 0;
    stream >> command;

    switch (command) {
    case CL_BET: {
        int playersBet = 0;
        stream >> playersBet;
        qDebug() << playersBet;
        emit bet(playersBet);
        break;
    }
    case CL_FOLD: {
        emit fold();
        break;
    }
    case CL_RAISE: {
        int amount = 0;
        stream >> amount;
        emit raise(amount);
        break;
    }
    case CL_ALLIN: {
        emit allIn();
        break;
    }
    case CL_CALL: {
        emit call();
        break;
    }
    case CL_CHECK: {
        emit check();
        break;
    }
    case CL_ROOM_CHOICE: {
        int room = 0;
        stream >> room;
        emit roomChosen(room);
        break;
    }
    }
}
