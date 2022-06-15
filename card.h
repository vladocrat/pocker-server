#ifndef CARD_H
#define CARD_H

#include <QObject>

class Card : public QObject
{
Q_OBJECT
public:
    enum Suit{
        DIAMONDS,
        HEARTS,
        CLUBS,
        SPADES
    };
    Q_ENUM(Suit);

    enum Value {
        TWO = 2,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK,
        QUEEN,
        KING,
        ACE
    };
    Q_ENUM(Value);

public:
    Card();
    Card(const Card&);
    Card& operator=(const Card&);

    const QString toString() const;
    const Suit& suit() const;
    const Value& value() const;
    void setSuit(const Suit&);
    void setValue(const Value&);

private:
    template<class T>
    QString enumToString(const T&) const;

    Suit m_suit;
    Value m_value;
};

#endif // CARD_H
