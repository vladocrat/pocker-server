#ifndef SERVER_H
#define SERVER_H

#include <QString>
#include <QVector>
#include <QObject>
#include <QTcpServer>

#include "user.h"
#include "room.h"

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(Room* room, QObject *parent = nullptr);

    ~Server();

private slots:
    void newUser();
    void onConnectionLost(User*);

private:
    void initServer();

    QTcpServer* tcpServer = nullptr;
    QVector<User*> users;
    Room* m_room = nullptr;
};
#endif
