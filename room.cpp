#include "room.h"
#include "protocol.h"

Room::Room()
{
    m_logic = new GameLogic();

    for (auto& player : m_players) {
        m_logic->setInitialHand(player);
    }

    m_table = m_logic->setInitialTable();
}

const int Room::bet() const
{
    return m_bet;
}

const int Room::bank() const
{
    return m_bank;
}

void Room::addToTable(Card card)
{
    m_table.append(card);
}

void Room::setPlayer(Player* player)
{
    qDebug() << Q_FUNC_INFO;

    connect(player, &User::bet, m_logic, &GameLogic::bet);
    connect(player, &User::check, m_logic, &GameLogic::check);
    connect(player, &User::fold, m_logic, &GameLogic::fold);
    connect(player, &User::allIn, m_logic, &GameLogic::allIn);
    connect(player, &User::raise, m_logic, &GameLogic::raise);
    connect(player, &User::call, m_logic, &GameLogic::call);

    connect(m_logic, &GameLogic::onBet, this, &Room::notifyBet);
    connect(m_logic, &GameLogic::onRaise, this, &Room::notifyRaise);
    connect(m_logic, &GameLogic::onAllIn, this, &Room::notifyAllIn);
    connect(m_logic, &GameLogic::onFold, this, &Room::notifyFold);
    connect(m_logic, &GameLogic::onCall, this, &Room::notifyCall);
    connect(m_logic, &GameLogic::onCheck, this, &Room::notifyCheck);

    m_players.append(player);
}

//TODO
//all notify functions must spread info aobut turns across all of the other players on every action.
void Room::notifyBet(Player* player)
{
    qDebug() << Q_FUNC_INFO;
    int bet = player->bet();
    m_bank += bet;

    notifyAllPlayers(CL_BET, bet);
}

void Room::notifyRaise(Player* player, int bet)
{
    qDebug() << Q_FUNC_INFO;
    notifyAllPlayers(CL_RAISE, bet);
}

void Room::notifyAllIn(Player* player, int playersMoney)
{
    qDebug() << Q_FUNC_INFO;
    //should take money from an actual player and not what is recieved
    //should be a check if money are of enough amount.
    notifyAllPlayers(CL_ALLIN, playersMoney);
}

void Room::notifyFold(Player* player)
{
    qDebug() << Q_FUNC_INFO;
    //not sure how this supposed to tell others about the exact player.
    notifyAllPlayers(CL_FOLD);
}

void Room::notifyCall(Player* player)
{
    qDebug() << Q_FUNC_INFO;
    //same issue as with fold.
    notifyAllPlayers(CL_CALL);
}

void Room::notifyCheck(Player* player)
{
   qDebug() << Q_FUNC_INFO;
   //same issue as above.
   notifyAllPlayers(CL_CHECK);
}

void Room::notifyAllPlayers(int command, int money)
{
    for (auto &x : m_players) {
        x->readySend(command, money);
    }
}

