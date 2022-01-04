#ifndef SERVER_H
#define SERVER_H

#include <QString>
#include <QVector>
#include <QObject>
#include <QTcpServer>


class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);

    ~Server();

private slots:
    void newUser();
    void readMessage();

private:
    void initServer();

    QTcpServer *tcpServer = nullptr;
    QVector<QTcpSocket*> users;
};
#endif
