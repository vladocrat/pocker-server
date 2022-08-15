#ifndef USERCONNECTION_H
#define USERCONNECTION_H

#include <QObject>

#include "room.h"
#include "connection.h"

class UserConnection : public Connection
{
    Q_OBJECT
public:
    UserConnection();

    void init();

signals:
    void roomChosen(int roomId);
    void roomLeft();

private:
    void handleData();
};

#endif // USERCONNECTION_H
