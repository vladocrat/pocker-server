#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <QByteArray>
#include <QObject>
#include <QList>

#include "user.h"
#include "room.h"

class UserController : public QObject
{
    Q_OBJECT
public:
    static UserController* instance() {
        static UserController controller;
        return &controller;
    }

    void addRoom();
    void addUser(User*);
    bool findUserByName(const QString&) const;

signals:
    void userLeft(User* user);


private slots:
    void requestToJoin(int roomId);
    void updateRoomInfo(Room* room);

private:
    UserController() {};
    ~UserController();
    UserController(const UserController&) = delete;
    UserController(UserController&&) = delete;
    UserController& operator=(const UserController&) = delete;

    QList<User*> m_users;
    QVector<Room*> m_rooms;
};

#endif // USERCONTROLLER_H
