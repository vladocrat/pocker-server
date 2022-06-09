#include "card.h"

#include <QVariant>


Card::Card()
{

}

Card::Card(const Card& other)
{
    this->setValue(other.value());
    this->setSuit(other.suit());
}

Card& Card::operator=(const Card &other)
{
    Card card;
    card.setSuit(other.suit());
    card.setValue(other.value());
    return *this;
}

const Card::Suit &Card::suit() const
{
    return m_suit;
}

void Card::setSuit(const Suit& suit)
{
    m_suit = suit;
}

const Card::Value &Card::value() const
{
    return m_value;
}

void Card::setValue(const Value& value)
{
    m_value = value;
}

const QString Card::toString() const
{
    QString str = "";
    str.append("value: " + enumToString(m_value));
    str.append(", ");
    str.append("suit: " + enumToString(m_suit));
    return str;
}

template<class T>
QString Card::enumToString(const T& value) const
{
   return QVariant::fromValue(value).toString();
}
