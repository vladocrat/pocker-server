#include "usercontroller.h"

#include <algorithm>

#include "connections/userconnection.h"
#include "protocol.h"

UserController::~UserController()
{
    for (auto x: qAsConst(m_users)) {
        if (x) {
            delete x;
        }
    }
}

bool UserController::addRoom(Room* room)
{
    room->setId(m_lobbies.length());
    auto lobby = dynamic_cast<Lobby*>(room);

    if (!lobby) {
        return false;
    }

    m_lobbies.append(lobby);

    return true;
}

void UserController::addUser(User* user)
{
    m_users.append(user);
    connect(user, &User::enterRoom, this, &UserController::requestToJoin);
    connect(this, &UserController::userLeft, user, &User::sendLeft);
    connect(user->connection()->socket(), &QTcpSocket::disconnected, [this, user] () {
        for (auto lobby : qAsConst(m_lobbies)) {
            auto users = lobby->users();
            auto userIt = users.begin();

            while (userIt != users.end()) {
                if (*userIt == user) {
                    users.erase(userIt);
                }
            }
        }

        m_users.removeOne(user);
    });
}

bool UserController::findUserByName(const QString& name) const
{
    return std::find_if(m_users.begin(), m_users.end(), [&name](User* user) {
        return name == user->name();
    }) != m_users.end();
}

QVector<Lobby*> UserController::rooms() const
{
    return m_lobbies;
}

QByteArray UserController::serialiseRooms() const
{
    QByteArray arr;
    QDataStream stream(&arr, QIODevice::WriteOnly);
    stream << m_lobbies.size();

    for (auto lobby : m_lobbies) {
        stream << lobby->seresialse();
    }

    return arr;
}

void UserController::requestToJoin(int roomId)
{
    auto user = static_cast<User*>(sender());
    m_lobbies.value(roomId)->addUser(user);
}

void UserController::updateRoomInfo(Lobby* lobby)
{
    for (auto user: qAsConst(m_users)) {
        user->send(Protocol::Server::SV_ROOM_UPDATED, Lobby::serialise(static_cast<Room>(*lobby)));
    }
}





