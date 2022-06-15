#ifndef ROOM_H
#define ROOM_H

#include <QObject>

#include "player.h"
#include "card.h"
#include "gamelogic.h"

class Room : public QObject
{
    Q_OBJECT;
public:
    Room();
    const int bet() const;
    const int bank() const;
    void addToTable(Card);

public slots:
    void setPlayer(Player*);
    void notifyBet(Player*);
    void notifyRaise(Player*, int bet);
    void notifyAllIn(Player*, int playersMoney);
    void notifyFold(Player*);
    void notifyCall(Player*);
    void notifyCheck(Player*);

signals:
    void onBet(int bank, int bet);
    void onRaise(int command, int money);
    void onAllIn(int command, int money);
    void onCall(int command, int money);
    void onFold(int command, int money);
    void onCheck(int command, int money);

private:
    void notifyAllPlayers(int command, int money = -1);


private:
    QVector<Player*> m_players;
    QVector<Card> m_table;
    GameLogic* m_logic = nullptr;
    //the bet that is currently in the game/round.
    int m_bet = 0;
    int m_bank = 0;
};

#endif // ROOM_H
