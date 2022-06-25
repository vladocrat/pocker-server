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

    void addUser(User*);
    //bool findUser(const User&);
    bool findUserByName(const QString&);

public slots:
    void onRoomChosen(int roomId);
    void onRoomExited();

private:
    UserController() {};
    ~UserController()
    {
        for (auto x: qAsConst(m_users)) {
            if (x) {
                delete x;
            }
        }
    }

    UserController(const UserController&) = delete;
    UserController(UserController&&) = delete;
    UserController& operator=(const UserController&) = delete;

    QList<User*> m_users;
};

#endif // USERCONTROLLER_H
