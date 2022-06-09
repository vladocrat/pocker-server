#include "gamelogic.h"

GameLogic::GameLogic()
{
    initDeck();
    shuffle();
    //printDeck();
}

QVector<Card> GameLogic::setInitialTable()
{
    //TODO??
   //store references instead if perfomance needed
    QVector<Card> table;
    table.append(m_deck[0]);
    table.append(m_deck[1]);
    table.append(m_deck[2]);
    m_deck.remove(0);
    m_deck.remove(1);
    m_deck.remove(2);
    return table;
}

void GameLogic::setInitialHand(Player *player)
{    
    player->setHand({m_deck[0], m_deck[1]});
    m_deck.remove(0);
    m_deck.remove(1);
}

void GameLogic::shuffle()
{
    srand(time(0));

    for (int i = 0; i < 52; ++i) {
        int randomPos = i + (rand() % (52 - i));
        swap(m_deck[i], m_deck[randomPos]);
    }
}

void GameLogic::swap(Card& firstCard, Card& secondCard)
{
    Card card(firstCard);
    firstCard = secondCard;
    secondCard = card;
}

void GameLogic::initDeck()
{
    Card::Value enumFirstElem = Card::Value::TWO;
    Card::Value enumLastElem = Card::Value::ACE;
    for (int i = 0; i < 4; ++i) {
        for (int j = enumFirstElem; j <= enumLastElem; ++j) {
            Card card;
            switch (i) {
            case 0:
                card.setSuit(Card::Suit::DIAMONDS);
                break;

            case 1:
                card.setSuit(Card::Suit::CLUBS);
                break;

            case 2:
                card.setSuit(Card::Suit::SPADES);
                break;

            case 3:
                card.setSuit(Card::Suit::HEARTS);
                break;
            }

            Card::Value value = static_cast<Card::Value>(j);
            card.setValue(value);
            m_deck.append(card);
        }
    }
}

void GameLogic::printDeck() const
{
    for (auto& card : m_deck) {
        qDebug() << card.toString();
    }
}

void GameLogic::bet(int bet)
{
    qDebug() << Q_FUNC_INFO;
    Player* player = static_cast<Player*>(sender());
    if (bet > player->money()) {
           return;
    }
    player->setBet(bet);
    emit onBet(player);
}

void GameLogic::fold()
{
    // player essentialy leaves the game
    // should the player be excluded by the room?
    Player* player = static_cast<Player*>(sender());
    emit onFold(player);
}

void GameLogic::raise(int raiseBy)
{
    Player* player = static_cast<Player*>(sender());
    //TODO
    //mb return like an error msg
    //but this shouldn't be possible, at the first place
    if (raiseBy > player->money()) {
        return;
    }
    emit onRaise(player, raiseBy);
}

void GameLogic::allIn()
{
    Player* player = static_cast<Player*>(sender());
    emit onAllIn(player, player->money());
}

void GameLogic::call()
{
    //only possible if no other players have placed a bet yet.
    //so another check is required.
    //maybe make an additional counter in the room class.
    Player* player = static_cast<Player*>(sender());
    emit onCall(player, player->money());
}

void GameLogic::check()
{
    Player* player = static_cast<Player*>(sender());
    emit onCheck(player);
}
