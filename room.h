#ifndef ROOM_H
#define ROOM_H

#include <QList>
#include <QObject>

#include "user.h"
#include "gamelogic.h"

class Room : QObject
{
    Q_OBJECT
public:
    Room();

public slots:
    void onUserJoined(); // member function

signals:
    void onUserLeft(const User*); // correct

private:
    QList<User> m_users;
    GameLogic m_logic;
};

#endif // ROOM_H
