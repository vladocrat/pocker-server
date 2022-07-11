#include "room.h"
#include "protocol.h"

Room::Room(int id) : m_id(id)
{

}

Room::Room()
{

}

Room& Room::operator=(const Room& other)
{
//    if (this == &other) {
//        return *this;
//    }

//    m_name =

    return *this;
}

bool Room::addUser(User* user)
{
    //TODO set signals
    //TODO check if able to join room
    if (m_users.count() >= m_maxPlayerCount) {
        qDebug() << "exсeeds max amount of players";

        return false;
    }

    m_users.append(user);
    initUser(user);

    return true;
}

int Room::id() const
{
    return m_id;
}

void Room::onUserLeft()
{
    auto user = static_cast<User*>(sender());

    if (!m_users.removeOne(user)) {
        qDebug() << "failed to exit room";
        user->closeConnection();
    }
}

void Room::initUser(User* user)
{
    QByteArray arr;
    QDataStream stream(arr);
    stream << m_id;
    user->send(Protocol::Server::SV_JOINED_SUCCESSFULLY, arr);
}
