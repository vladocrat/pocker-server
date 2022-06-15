#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <QObject>
#include <QString>

#include "user.h"
#include "LoginData.h"
#include "RegisterData.h"

class UserRepository : public QObject
{
    Q_OBJECT
public:
    explicit UserRepository(QObject *parent = nullptr);
    //singleton?

    static bool removeUser(const User&);
    static bool registerUser(const RegisterData&);
    static bool login(const LoginData&, User&);
};

#endif // USERREPOSITORY_H
