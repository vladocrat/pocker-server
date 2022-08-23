#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <QByteArray>
#include <QObject>
#include <QList>

#include "user.h"
#include "lobby.h"
#include "room.h"

class UserController : public QObject
{
    Q_OBJECT
public:
    static UserController* instance() {
        static UserController controller;
        return &controller;
    }

    void addRoom(Room*);
    void addUser(User*);
    bool findUserByName(const QString&) const;
    QVector<Lobby*> lobbies();

signals:
    void userLeft(User* user);

private slots:
    void requestToJoin(int roomId);
    void updateRoomInfo(Lobby* room);

private:
    UserController() {};
    ~UserController();
    UserController(const UserController&) = delete;
    UserController(UserController&&) = delete;
    UserController& operator=(const UserController&) = delete;

    QList<User*> m_users;
    QVector<Lobby*> m_lobbies;
};

#endif // USERCONTROLLER_H
