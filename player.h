#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QVector>
#include <QString>

#include "user.h"
#include "card.h"

class Player : public User
{
    Q_OBJECT;
public:
    Player(QVector<Card> hand);
    ~Player();

    const QVector<Card> hand() const;
    void setHand(QVector<Card>);

    const int bet() const;
    void setBet(int bet);

    const int money() const;
    void setMoney(int money);

    const QString toString() const;

private:
    QVector<Card> m_hand;
    int m_money = 0;
    int m_bet = 0;
};
#endif // PLAYER_H
