#include <QDataStream>

#include "user.h"
#include "protocol.h"

User::User(const User& user)
{
   m_profile = user.m_profile;
}

void User::setProfile(const Profile& profile)
{
    m_profile = profile;
}

QByteArray User::serialize() const
{
    QByteArray data;
    QDataStream stream(data);
    stream << *this;

    return data;
}

QDataStream& operator<<(QDataStream& out, const User& user)
{
    out << user.m_profile;
    return out;
}

void User::handleClientCommand()
{

}


