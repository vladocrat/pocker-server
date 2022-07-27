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

void UserController::addRoom(Room* room)
{
    auto lobby = dynamic_cast<Lobby*>(room);

    if (!lobby) {
        return;
    }

    room->setId(m_rooms.length() - 1);
    m_rooms.append(lobby);
}

void UserController::addUser(User* user)
{
    m_users.append(user);
    connect(user, &User::enterRoom, this, &UserController::requestToJoin);
    connect(this, &UserController::userLeft, user, &User::sendLeft);
}

bool UserController::findUserByName(const QString& name) const
{
    return std::find_if(m_users.begin(), m_users.end(), [&name](User* user) {
        return name == user->name();
    }) != m_users.end();
}

void UserController::requestToJoin(int roomId)
{
    auto user = static_cast<User*>(sender());
    qDebug() << m_rooms.value(roomId);
    auto r = m_rooms.value(roomId);
    m_rooms.value(roomId)->addUser(user);
}

void UserController::updateRoomInfo(Lobby* lobby)
{
    //TODO barr
    for (auto user: qAsConst(m_users)) {
        user->send(Protocol::Server::SV_ROOM_UPDATED, Lobby::serialise(static_cast<Room>(*lobby)));
    }
}





