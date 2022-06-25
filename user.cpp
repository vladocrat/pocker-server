#include <QDataStream>

#include "user.h"
#include "../common/protocol.h"

User::User(UserConnection* socket)
{
    assert(socket);
    m_socket = socket;
}

User::User(const User& user)
{
    m_profile = user.m_profile;
}

User::~User()
{
    assert(m_socket);
    m_socket->socket()->close();
    m_socket->deleteLater();
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
    return m_socket;
}

QDataStream& operator<<(QDataStream& out, const User& user)
{
    out << user.m_profile;

    return out;
}

void User::handleClientCommand()
{

}


