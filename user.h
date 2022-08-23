#ifndef USER_H
#define USER_H

#include <QTcpSocket>
#include <QObject>
#include <QString>
#include <memory>
#include <assert.h>

#include "profile.h"
#include "card.h"
#include "connections/userconnection.h"
#include "connections/pendingconnection.h"

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(UserConnection* socket);
    User(const User&);
    ~User();

    void setProfile(const Profile&);
    QString toString() const;
    QByteArray serialize() const;
    QString name() const;
    UserConnection* connection() const;
    Profile profile() const;
    void closeConnection();
    void sendCommand(int command) const;
    void send(int command, const QByteArray&);

    bool operator==(const User&) const;

signals:
    void enterRoom(int roomId);
    void leaveRoom();
    // etc

    // game side signals
    // void makeBet
    // etc
public slots:
    void sendLeft();

private:
    friend QDataStream& operator<<(QDataStream&, const User&);

    UserConnection* m_connection;
    Profile m_profile;
    struct GameData {
        QVector<Card> m_hand;
        int m_money = 0;
        int m_bet = 0;
    };

    std::unique_ptr<GameData> m_gameDataImpl;
};


#endif // USER_H
