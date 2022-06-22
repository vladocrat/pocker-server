#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QDataStream>

struct Message
{
    QByteArray serialize() const
    {
        QByteArray arr;
        QDataStream stream(arr);
        stream << msg;

        return arr;
    }

    QString msg;
};

#endif // MESSAGE_H
