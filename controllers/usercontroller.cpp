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

void UserController::addRoom()
{
    auto room = new Room(m_rooms.size());
    m_rooms.append(room);
    connect(room, &Room::update, this, &UserController::updateRoomInfo);
    //TODO doesnt work:)
//    connect(&room, &Room::onUserLeft, [this] () {
//           //emit userLeft(user);
//    });
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
    m_rooms.value(roomId)->addUser(user);
}

void UserController::updateRoomInfo(Room *room)
{
    //TODO barr
    for (auto user: m_users) {
        user->send(Protocol::Server::SV_ROOM_UPDATED, QByteArray());
    }
}





