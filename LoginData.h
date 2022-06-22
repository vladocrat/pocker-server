#ifndef LOGINDATA_H
#define LOGINDATA_H

#include <QString>
#include <QDataStream>

struct LoginData
{
    QByteArray serialize() const
    {
        QByteArray arr;
        QDataStream stream(arr);
        stream << login << password;

        return arr;
    }

    QString login;
    QString password;
};

#endif // LOGINDATA_H
