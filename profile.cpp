#include "profile.h"

#include <QDebug>
#include <QIODevice>

QDataStream& operator<<(QDataStream& out, const Profile& profile)
{
    out << profile.name
        << profile.email
        << profile.pfpLink;

    return out;
}

bool Profile::operator==(const Profile& profile) const
{
    if (this->name != profile.name) {
        return false;
    }

    if (this->email != profile.email) {
        return false;
    }

    if (this->pfpLink != profile.pfpLink) {
        return false;
    }

    return true;
}

QByteArray Profile::serialize() const
{
    QByteArray arr;
    QDataStream stream(&arr, QIODevice::WriteOnly);
    stream << name
           << email
           << pfpLink;

    return arr;
}

QString Profile::toString() const
{
    return { name + " " + email + " " + pfpLink };
}
