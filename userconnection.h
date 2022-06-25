#ifndef USERCONNECTION_H
#define USERCONNECTION_H

#include <QObject>

#include "connection.h"

class UserConnection : public Connection
{
    Q_OBJECT
public:
    UserConnection();

    void init();

private:
    void handleData();
};

#endif // USERCONNECTION_H
