#ifndef USER_H
#define USER_H

#include <QTcpSocket>
#include <QObject>


class User : public QObject
{
    Q_OBJECT
public:
    User(const QString& login = "default");

    ~User();
    QTcpSocket* socket() const;
    QString login() const;

    void setSocket(QTcpSocket*);

public slots:
    void readySend(int command, int money = -1);

private slots:
    void readMessage();
    void writeMessage(int command, int money = -1);
    void onSocketDisconnected();


signals:
    void onUserConnectionLost(User*);
    void onUserConnected();

    void bet(int);
    void fold();
    void raise(int);
    void allIn();
    void call();
    void check();


private:
    void handleData(const QByteArray&);

    QTcpSocket* m_socket = nullptr;  // coz socket is null ptr (need to initialize) we are not able to connect? or some shit
    QString m_login = "";
    int m_packageSize = -1;
};

#endif // USER_H
