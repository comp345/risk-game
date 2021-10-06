#include<iostream>
#include<string>
#include"Cards.h"
using namespace std;


// **************** //
// Card functions:  //
// **************** //
Card::Card(Effect value)
{
    m_effect = new Effect(value);
}

Card::~Card()
{
    delete m_effect;
}

void Card::play(Player& player, Deck& deck)
{
    player.add_to_orders(static_cast<int>(*m_effect));
    deck.returnCard(this);
}



std::ostream& operator<<(std::ostream& lhs, Card::Effect* e) 
{
    switch (*e)
    {
    case Card::Effect::bomb:
        return lhs << "Bomb";
        break;
    case Card::Effect::reinforcement:
        return lhs << "reinforcement";
        break;
    case Card::Effect::blockade:
        return lhs << "blockade";
        break;
    case Card::Effect::airlift:
        return lhs << "airlift";
        break;
    case Card::Effect::diplomacy:
        return lhs << "diplomacy";
        break;
    }
    return lhs;
}
std::ostream& operator<<(std::ostream& lhs, Card* card) 
{
    return lhs << card->m_effect;
}

Card::Effect* Card::getEffect()
{
    return m_effect;
}


// **************** //
// Deck functions:  //
// **************** //
Deck::Deck(int size)
{
    initialize(size);
}

void Deck::initialize(int size)
{
    for(int i=0; i < size; i++)
    {
        int randomNumber = rand() % 5;
        Card::Effect card = static_cast<Card::Effect>(randomNumber);
        m_cards.push_back(new Card(card));
    }

    while (!validate(m_cards))
    {
        initialize(size);
    }   
}

Deck::~Deck()
{
    m_cards.clear();
}

bool Deck::validate(vector<Card*> cards)
{
    // Create an array with an index for each possible card value
    int sum[5] = {};
    for(Card* card: cards)
    {
        // Convert the cards effect enum to an int, then increment the value at that index
        sum[static_cast<int>(*card->getEffect())] += 1;
    }


    cout << "There is,\n";
    for(int i = 0; i < 5; i++)
    {
        cout << sum[i] << " " << new Card(Card::Effect(i)) << " cards\n";
        if(sum[i] == 0)
        {
            cout << "Validation failed.";
            return false;
        }
    }

    cout << "\n";
    return true;
}

void Deck::showDeck()
{
    int count = 1;
    cout << "\nThe deck currently contains:\n";
    for(Card* i: m_cards)
    {
        std::cout << count++ << ": " << i << "\n";
    }
}

void Deck::draw(Player& player)
{
    // Fetches the players hand and the card that will be drawn
    Hand* playerHand = player.getHand();
    Card* toDraw = m_cards.back();
    playerHand->drawCard(toDraw);

    cout << "Player: " << player.getName() << " drew a " << toDraw << "\n";

    //Removes the card from the deck
    m_cards.pop_back();
}

void Deck::returnCard(Card* card)
{
    m_cards.push_back(card);
}






// **************** //
// Hand functions:  //
// **************** //
Hand::Hand(/* args */)
{
}

Hand::~Hand()
{
    m_cards.clear();
}
void Hand::drawCard(Card* card)
{
    m_cards.push_back(card);
}
void Hand::showCards(Player player)
{
    cout << "\nPlayer: " << player.getName() << " currently has the following cards\n";
    for(Card* i: m_cards)
    {
        std::cout << i << " card\n";
    }

}
Card* Hand::useLast()
{
    Card* toUse = m_cards.back();
    m_cards.pop_back();
    return toUse;
}



// ****************** //
// Player functions:  //
// ****************** //
Player::Player(string name)
{
    m_name = name;
    m_hand = new Hand();
}

void Player::add_to_orders(int value)
{
    m_orders.push_back(value);
}

void Player::showOrders()
{
    cout << "\nPlayer: " << m_name << " Has the following ordered queued\n";
    for(int id: m_orders)
    {
        cout << new Card(static_cast<Card::Effect>(id)) << "\n";
    }
}

string Player::getName()
{
    return m_name;
}

Hand* Player::getHand()
{
    return m_hand;
}

Player::~Player()
{
    m_orders.clear();
}




