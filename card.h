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
    Q_ENUM(Suit);

public:
    Card();
    Card(const Card&);

    Card& operator=(const Card&);

    const Suit& suit() const;
    void setSuit(const Suit&);

    const Value& value() const;
    void setValue(const Value&);

    const QString toString() const;

private:
    template<class T>
    QString enumToString(const T&) const;

    Suit m_suit;
    Value m_value;
};

#endif // CARD_H
