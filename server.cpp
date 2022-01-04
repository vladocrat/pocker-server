#include <QtCore>
#include <QTcpSocket>
#include <QDebug>

#include "server.h"

Server::Server(QObject *parent)
{
    initServer();
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::newUser);

}

Server::~Server()
{
    tcpServer->close();
    for (auto& x : users) {
        x->close();
        x->deleteLater();
    }
    tcpServer->deleteLater();
}

void Server::initServer()
{
    tcpServer = new QTcpServer(this);
    QHostAddress address("127.0.0.1");
    if (!tcpServer->listen(address, 7890)) {
        return;
    }
}

void Server::newUser()
{
    qDebug() << Q_FUNC_INFO;
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, &QTcpSocket::readyRead, this, &Server::readMessage);
    users.append(clientConnection);
}

void Server::readMessage()
{
    qDebug() << Q_FUNC_INFO;
    QTcpSocket* client = static_cast<QTcpSocket*>(sender());
    if (client->bytesAvailable() > 0) {
        int size = client->bytesAvailable();
        char buffer[100];
        client->read(&buffer[0], size);
        buffer[size] = '\0';
        for (int i = 0; i < size; i++) {
           qDebug()  << buffer[i];
        }
    }
}

void Server::onDisconnect()
{

}
