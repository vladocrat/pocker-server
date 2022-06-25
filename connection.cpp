#include "connection.h"

#include <QDataStream>
#include <assert.h>

#include "../common/protocol.h"

Connection::Connection()
{
    m_socket = new QTcpSocket;
}

Connection::~Connection()
{
    assert(m_socket);

    if (m_socket) {
        m_socket->close();
        m_socket->deleteLater();
    }
}

bool Connection::sendCommand(int command)
{
    if (!checkConnection()) return false;

    QByteArray msg;
    QDataStream stream(&msg, QIODevice::WriteOnly);
    QDataStream socketStream(m_socket);
    stream << command;
    socketStream << msg.size() << msg;
    m_socket->flush();

    return true;
}

bool Connection::send(int command, const QByteArray &data)
{
    if (!checkConnection()) return false;

    QByteArray msg;
    QDataStream stream(&msg, QIODevice::WriteOnly);
    QDataStream socketStream(m_socket);
    stream << command << data;
    socketStream << msg.size() << msg;
    m_socket->flush();

    return true;
}

void Connection::readUserData(QByteArray& data)
{
    QDataStream another(m_socket);

    if ((m_socket->bytesAvailable() >= sizeof(int)) && m_packageSize == -1) {
        another >> m_packageSize;
    } else {
        return;
    }

    if (m_socket->bytesAvailable() < m_packageSize) {
        return;
    }

    another >> data;
    m_packageSize = -1;
}

int Connection::readCommand(QDataStream &stream)
{
    int command = 0;
    stream >> command;

    return command;
}

QTcpSocket* Connection::clearSocket()
{
    if (!m_socket->disconnect()) {
        qDebug() << "failed to disconnect socket handlers";

        if (!sendCommand(Protocol::Errors::SV_INTERNAL_SERVER_ERR)) {
            qDebug() << "failed to send";
        }

        m_socket->close();

        return nullptr;
    }

    auto copy = m_socket;
    m_socket = nullptr;

    return copy;
}

QTcpSocket* Connection::socket() const
{
    return m_socket;
}

void Connection::setScoket(QTcpSocket* socket)
{
    m_socket = socket;
}

bool Connection::checkConnection() const
{
    if (m_socket->state() != QTcpSocket::ConnectedState) {
        qDebug() << "socket not connected";

        return false;
    }

    return true;
}
