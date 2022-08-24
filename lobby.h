#ifndef LOBBY_H
#define LOBBY_H

#include <QObject>

#include "room.h"
#include "user.h"
#include "gamelogic.h"

class Lobby : public Room
{
    Q_OBJECT
public:
    Lobby();
    Lobby(const Room&);
    ~Lobby();

    bool addUser(User*);
    GameLogic logic() const;
    QList<User*> users() const;
    void setLogic(const GameLogic&);

    static void deserialise(const QByteArray&);
    QByteArray seresialse() const;

private slots:
    void onUserLeft();

signals:
    void update(Room* room);

private:
    void initUser(User* user);
    void notifyUsers() const;

    GameLogic m_logic;
    QList<User*> m_users;
};

#endif // LOBBY_H
