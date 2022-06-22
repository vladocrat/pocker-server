#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>

#include "card.h"

class GameLogic : public QObject
{
    Q_OBJECT;
public:
    GameLogic();

private:
    void shuffle();
    void swap(Card&, Card&);
    void initDeck();

    QVector<Card> m_deck;
};

#endif // GAMELOGIC_H
