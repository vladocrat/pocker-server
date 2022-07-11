#ifndef ROOM_H
#define ROOM_H

#include <QList>
#include <QObject>

#include "user.h"
#include "gamelogic.h"

class Room : public QObject
{
    Q_OBJECT
public:
    Room(int id);
    Room();
    Room(const Room&) {};
    Room& operator=(const Room& other);

    bool addUser(User*);
    int id() const ;

private slots:
    void onUserLeft();

signals:
    void update(Room* room);

private:
    void initUser(User* user);

    QList<User*> m_users;
    GameLogic m_logic;
    int m_maxPlayerCount = 4; // can be set by user creating the room.
    int m_id = -1;
};

#endif // ROOM_H
