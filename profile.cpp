#include "profile.h"

#include <QDebug>
#include <QIODevice>

QDataStream& operator<<(QDataStream& out, const Profile& profile)
{
    out << profile.name
        << profile.email
        << profile.pfpLink
        << profile.wins
        << profile.loses
        << profile.totalSpent
        << profile.totalWon;

    return out;
}

QByteArray Profile::serialize() const
{
    QByteArray arr;
    QDataStream stream(&arr, QIODevice::WriteOnly);
    stream << name
           << email
           << pfpLink
           << wins
           << loses
           << totalSpent
           << totalWon;

    return arr;
}

QString Profile::toString() const
{
    return { name + " " + email + " " + pfpLink };
}
