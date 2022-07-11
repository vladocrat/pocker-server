#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QObject>
#include <QByteArray>

#include "connections/pendingconnection.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    static Server* instance()
    {
        static Server s;
        return &s;
    }

    void listen();
    void setAddress(const QHostAddress& address);
    void setAddress(const QString& address);
    void setPort(int port);
    QHostAddress address();
    int port();

public slots:
    void authorised(const Profile&);

protected:
    void incomingConnection(qintptr handle) override;

private:
    Server();
    ~Server();
    Server(const Server&) = delete;
    Server(Server&&) = delete;
    Server& operator=(const Server&) = delete;

    QHostAddress m_address = QHostAddress::Any;
    int m_port = 0;
    QList<PendingConnection*> m_pendingConnections;
};
#endif // SERVER_H
