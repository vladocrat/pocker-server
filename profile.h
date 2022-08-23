#ifndef PROFILE_H
#define PROFILE_H

#include <QByteArray>
#include <QString>
#include <QDataStream>

struct Profile
{
    friend QDataStream& operator<<(QDataStream&, const Profile&);

    QByteArray serialize() const;
    QString toString() const;

    QString pfpLink;
    QString name;
    QString email;
    int wins;
    int loses;
    int totalSpent;
    int totalWon;
};

#endif // PROFILE_H
