#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>

#include "card.h"
#include "player.h"

class GameLogic : public QObject
{
    Q_OBJECT;
public:
    GameLogic();

    QVector<Card> setInitialTable();
    void setInitialHand(Player* player);
    void printDeck() const;
    //TODO
    //add one card to the table

public slots:
    void bet(int);
    void fold();
    void raise(int);
    void allIn();
    void call();
    void check();

signals:
    void onBet(Player*);
    void onRaise(Player*, int bet);
    void onAllIn(Player*, int playersMoney);
    void onCall(Player*, int playersMoney);
    void onFold(Player*);
    void onCheck(Player*);

private:
    void shuffle();
    void swap(Card&, Card&);
    void initDeck();

    QVector<Card> m_deck;
};

#endif // GAMELOGIC_H
