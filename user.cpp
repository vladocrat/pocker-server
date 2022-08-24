#include <QDataStream>

#include "user.h"
#include "protocol.h"

User::User(UserConnection* socket)
{
    assert(socket);
    m_connection = socket;
    connect(m_connection, &UserConnection::roomChosen, this, &User::enterRoom);
    connect(m_connection, &UserConnection::roomLeft, this, &User::leaveRoom);
}

User::User(const User& user)
{
    m_profile = user.m_profile;
}

User::~User()
{
    assert(m_connection);
    m_connection->socket()->close();
    m_connection->deleteLater();
}

void User::setProfile(const Profile& profile)
{
    m_profile = profile;
}

QString User::toString() const
{
    return m_profile.toString();
}

QByteArray User::serialize() const
{
    return m_profile.serialize();;
}

QString User::name() const
{
    return m_profile.name;
}

UserConnection *User::connection() const
{
    return m_connection;
}

Profile User::profile() const
{
    return m_profile;
}

void User::closeConnection()
{
    m_connection->socket()->close();
}

void User::sendCommand(int command) const
{
    if (!m_connection->sendCommand(command)) {
        qDebug() << "failed to send";
         m_connection->socket()->close();
    }
}

void User::send(int command, const QByteArray& data)
{
    if (!m_connection->send(command, data)) {
        qDebug() << "failed to send";
        m_connection->socket()->close();
    }
}

bool User::operator==(const User& user) const
{
    return m_profile == user.profile();
}

void User::sendLeft()
{
    if (!connection()->sendCommand(Protocol::Server::SV_LEFT_SUCCESSFULLY)) {
        qDebug() << "faild to send command";
        //TODO do nothing?
    }
}

QDataStream& operator<<(QDataStream& out, const User& user)
{
    out << user.m_profile;

    return out;
}



