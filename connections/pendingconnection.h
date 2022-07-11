#ifndef PENDINGCONNECTION_H
#define PENDINGCONNECTION_H

#include <QByteArray>
#include <QObject>

#include "connection.h"
#include "userconnection.h"
#include "profile.h"

class PendingConnection : public Connection
{
    Q_OBJECT;
public:
    PendingConnection();

signals:
    void logged(const Profile& profile);

private:
    void handleData();
};

#endif // PENDINGCONNECTION_H
