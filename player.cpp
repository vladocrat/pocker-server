#include "player.h"

Player::Player(QVector<Card> hand)
{
    m_hand = hand;
    m_money = 1000;
}

Player::~Player()
{
    m_hand.clear();
}

const QVector<Card> Player::hand() const
{
    return m_hand;
}

void Player::setHand(QVector<Card> hand)
{
    m_hand = hand;
    //ix of deck cards
}

const int Player::bet() const
{
    return m_bet;
}

void Player::setBet(int bet)
{
    m_bet = bet;
}

const int Player::money() const
{
    return m_money;
}

void Player::setMoney(int money)
{
    m_money = money;
}

const QString Player::toString() const
{
    QString string = "";
    string.append("bet: " + QString::number(m_bet));
    string.append(", ");
    string.append("money: " + QString::number(m_money));
    return string;
}

