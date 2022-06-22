#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QObject>
#include <QByteArray>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    //TODO make singleton
    Server(QHostAddress address, int port = 0);
    ~Server();

protected:
    void incomingConnection(qintptr handle) override;

private:
    void handleData(QTcpSocket*,const QByteArray&);

    int m_packageSize = -1;
    QList<QTcpSocket*> m_pendingConnections;
};
#endif // SERVER_H
