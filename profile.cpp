#include "profile.h"

QDataStream& operator<<(QDataStream& out, const Profile& profile)
{
    out << profile.name
        << profile.email
        << profile.pfpLink;
    return out;
}

QString Profile::toString()
{
    return { name + " " + email + " " + pfpLink };
}
