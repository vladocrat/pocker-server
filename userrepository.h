#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <QObject>
#include <QString>
#include <QtSql/QSqlDatabase>

#include "user.h"
#include "LoginData.h"
#include "RegisterData.h"

class UserRepository : public QObject
{
    Q_OBJECT
public:
    static UserRepository* instance() {
        static UserRepository ur;
        return &ur;
    }

    bool removeUser(const User&);
    bool registerUser(const RegisterData&);
    bool login(const LoginData&, User&);
    bool userExists(const RegisterData&, bool* ok = nullptr);
    bool userExists(const LoginData&, bool* ok = nullptr);
    bool findUserByName(const QString&, User&);
    bool findUserByEmail(const QString&, User&);

private:
    bool executeQuery(QSqlQuery& query);
    bool open();

    UserRepository();
    ~UserRepository();

    QSqlDatabase m_db;
};

#endif // USERREPOSITORY_H
