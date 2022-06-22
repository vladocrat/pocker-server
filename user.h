#ifndef USER_H
#define USER_H

#include <QTcpSocket>
#include <QObject>
#include <QString>
#include <memory>
#include <assert.h>

#include "profile.h"
#include "card.h"

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QTcpSocket* socket)
    {
        assert(socket);
        m_socket = socket;
    }
    User(const User&);
    ~User()
    {
        assert(m_socket);
        m_socket->close();
        //m_socket->deleteLater();
    }

    void setProfile(const Profile&);


    QString toString()
    {
        return m_profile.toString();
    }

    QByteArray serialize() const;

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

    QTcpSocket* m_socket;
    Profile m_profile;
    struct GameData {
        QVector<Card> m_hand;
        int m_money = 0;
        int m_bet = 0;
    };

    std::unique_ptr<GameData> m_gameDataImpl;
};


#endif // USER_H
