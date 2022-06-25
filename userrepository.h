#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <QObject>
#include <QString>
#include <QtSql/QSqlDatabase>

#include "user.h"
#include "../common/LoginData.h"
#include "../common/RegisterData.h"

class UserRepository : public QObject
{
    Q_OBJECT
public:
    static UserRepository* instance()
    {
        static UserRepository r;
        return &r;
    }

    bool removeUser(const User&);
    bool registerUser(const RegisterData&);
    bool login(const LoginData&, Profile&);
    bool userExists(const RegisterData&, bool* ok = nullptr);
    bool userExists(const LoginData&, bool* ok = nullptr);
    bool findUserByName(const QString&, User&);
    bool findUserByEmail(const QString&, User&);

private:
    UserRepository();
    ~UserRepository();
    UserRepository(const UserRepository&) = delete;
    UserRepository(UserRepository&&) = delete;
    UserRepository& operator=(const UserRepository&) = delete;

    bool executeQuery(QSqlQuery& query);
    bool open();

    QSqlDatabase m_db;
};

#endif // USERREPOSITORY_H
