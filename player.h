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
    const int bet() const;
    const int money() const;
    void setHand(QVector<Card>);
    void setBet(int bet);
    void setMoney(int money);
    const QString toString() const;

private:
    QVector<Card> m_hand;
    int m_money = 0;
    int m_bet = 0;
};
#endif // PLAYER_H
