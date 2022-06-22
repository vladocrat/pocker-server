#ifndef REGISTERDATA_H
#define REGISTERDATA_H

#include "LoginData.h"

struct RegisterData : public LoginData
{
    QByteArray serialize() const
    {
        QByteArray arr;
        QDataStream stream(arr);
        stream << login << password << email;

        return arr;
    }

    QString email;
};

#endif // REGISTERDATA_H
