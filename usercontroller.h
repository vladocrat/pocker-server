#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <QByteArray>
#include <QObject>
#include <QList>

#include "user.h"

class UserController : public QObject
{
    Q_OBJECT
public:
    static UserController* instance() {
        static UserController controller;
        return &controller;
    }

    bool addUser(const User&);
    const User& findUserByName(const QString&);

public slots:
    void onRoomChosen(int roomId);
    void onRoomExited();

private:
    UserController();
    UserController(const UserController&) = delete;
    UserController(UserController&&) = delete;
    UserController& operator=(const UserController&);

   // QList<User> m_users;

};

#endif // USERCONTROLLER_H
