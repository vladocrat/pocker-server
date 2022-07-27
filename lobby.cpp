#include "lobby.h"

#include "protocol.h"

Lobby::Lobby()
{
    //connect(room, &Lobby::update, this, &UserController::updateRoomInfo);
}

Lobby::Lobby(const Room& room)
{
    setId(room.id());
    setMaxPlayerCount(room.maxPlayerCount());
    setName(room.name());
    setStatus(room.status());
    setPlayerCount(room.playerCount());
    setAccess(room.access());
    setInitialBet(room.initialBet());
    setPassword(room.password());
}

Lobby::~Lobby()
{
    for (auto user : qAsConst(m_users)) {
        if (user) {
            delete user;
        }
    }
}

bool Lobby::addUser(User* user)
{
    //TODO set signals
    //TODO check if able to join room
    //TODO check password
    //TODO update room on client
    if (m_users.count() >= maxPlayerCount()) {
        //TODO return error
        qDebug() << "exceeds max amount of players";

        return false;
    }

    m_users.append(user);
    setPlayerCount(playerCount() + 1);
    initUser(user);

    return true;
}

QList<User*> Lobby::users() const
{
    return m_users;
}

void Lobby::setLogic(const GameLogic& logic)
{
    m_logic = logic;
}

void Lobby::deserialise(const QByteArray& data)
{
    Room::deserialise(data);
}

void Lobby::onUserLeft()
{
    auto user = static_cast<User*>(sender());

    if (!m_users.removeOne(user)) {
        qDebug() << "failed to exit room";
        user->closeConnection();
    }
}

void Lobby::initUser(User* user)
{
    user->send(Protocol::Server::SV_JOINED_SUCCESSFULLY, serialise(static_cast<Room>(*this)));
}

void Lobby::notifyUsers() const
{

}
