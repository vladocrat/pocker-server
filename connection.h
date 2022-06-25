#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>
#include <QObject>
#include <QByteArray>

class Connection : public QObject
{
    Q_OBJECT
public:
    Connection();
    virtual ~Connection();

    virtual bool sendCommand(int command);
    virtual bool send(int command, const QByteArray& data);
    virtual void readUserData(QByteArray&);
    virtual int readCommand(QDataStream&);

    QTcpSocket* clearSocket();

    QTcpSocket* socket() const;
    void setScoket(QTcpSocket* con);

private:
    bool checkConnection() const;

    QTcpSocket*  m_socket;
    int m_packageSize = -1;
};

#endif // CONNECTION_H
