#ifndef USER_H
#define USER_H

#include <QTcpSocket>
#include <QObject>
#include <QString>
#include <memory>
#include <assert.h>

#include "profile.h"
#include "card.h"
#include "userconnection.h"
#include "pendingconnection.h"

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

signals:
    // controller side signals
    //void enterRoom
    //void leaveRoom
    // etc

    // game side signals
    // void makeBet
    // etc

private slots:
    void handleClientCommand(); // socket readyRead
                                // read CL_* command, convert to according signal and emit
                                // UserController and room (if needed) connects to according signals.
private:
    friend QDataStream& operator<<(QDataStream&, const User&);

    UserConnection* m_socket;
    Profile m_profile;
    struct GameData {
        QVector<Card> m_hand;
        int m_money = 0;
        int m_bet = 0;
    };

    std::unique_ptr<GameData> m_gameDataImpl;
};


#endif // USER_H
