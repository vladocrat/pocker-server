#ifndef PROFILE_H
#define PROFILE_H

#include <QByteArray>
#include <QString>
#include <QDataStream>

struct Profile
{
    friend QDataStream& operator<<(QDataStream&, const Profile&);

    QString toString();

    QString pfpLink;
    QString name;
    QString email;
};
#endif // PROFILE_H
