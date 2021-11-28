#include<iostream>
#include<string>
#include "Card.h"
#include <ctime>
#include <cstdlib>
#include "Player.h"
using namespace std;

// Extra helper functions (Noah)
void initializedRand() // makes rand() "more" random
{
    srand(time(NULL));
}


// **************** //
// Card functions:  //
// **************** //
Card::Card(Effect value)
{
    m_effect = new Effect(value);
}

Card::Card(const Card& other)
{
    m_effect = other.m_effect;
}

Card::Card()
{

}

Card::~Card()
{
    delete m_effect;
}

// Creates an Order, and adds it to the players list of order
// Then removes that card from the deck
void Card::play(Player& player, Deck& deck)
{
    // A1 implementation 

    // player.issueOrder(Order::getOrder());
    deck.returnCard(this);
    // cout << "\n" << m_effect << " was played by " << player.getName() << "\n";
}


Card::Effect* Card::getEffect()
{
    return m_effect;
}

bool Card::validate()
{
    cout << "Validate Card order.";
    return true;
}
bool Card::execute()
{
    cout << "Execute Card order.";
    return true;
}

Card& Card::operator=(const Card& c)
{
    if (this == &c)
        return *this;

    m_effect = c.m_effect;
    return *this;
}

//Main write function responsible for the card class
std::ostream& Card::write(std::ostream &os) const
{
    cout << m_effect;
    return os;
}

std::ostream& operator<<(std::ostream& lhs, Card::Effect* e)
{
    switch (*e)
    {
        case Card::Effect::BOMB:
            return lhs << "Bomb";
        case Card::Effect::REINFORCEMENT:
            return lhs << "Reinforcement";
        case Card::Effect::BLOCKADE:
            return lhs << "Blockade";
        case Card::Effect::AIRLIFT:
            return lhs << "Airlift";
        case Card::Effect::DIPLOMACY:
            return lhs << "Diplomacy";
    }
    return lhs;
}
std::ostream& operator<<(std::ostream& lhs, Card* card)
{
    return lhs << card->m_effect;
}

std::ostream& operator<<(std::ostream& lhs, Card& card)
{
    return card.write(lhs);
}

// **************** //
// Bomb functions:  //
// **************** //
CardBomb::CardBomb(Card::Effect* effect) : Order("Bomb type", "")
{
    m_effect = effect;
}
CardBomb::~CardBomb()
{
    delete m_effect;
}
CardBomb::CardBomb(const CardBomb &b) : Order("Bomb type", "")
{
    m_effect = b.m_effect;
}
// function which is called when we are printing the name of each card.
std::ostream& CardBomb::write(std::ostream &os) const
{
    cout << m_effect;
    return os;
}

// **************** //
// Reinforcement functions:  //
// **************** //
Reinforcement::Reinforcement(Card::Effect* effect) : Order("Reinforcement type", "")
{
    m_effect = effect;
}

Reinforcement::Reinforcement(const Reinforcement& other) : Order("Reinforcement type", "")
{
    m_effect = other.m_effect;
}

Reinforcement::~Reinforcement()
{
    delete m_effect;
}

// function which is called when we are printing the name of each card.
std::ostream& Reinforcement::write(std::ostream &os) const
{
    cout << m_effect;
    return os;
}

// **************** //
// Blockade functions:  //
// **************** //
CardBlockade::CardBlockade(Card::Effect* effect) : Order("Blockade type", "")
{
    m_effect = effect;
}

CardBlockade::CardBlockade(const CardBlockade& other) : Order("Blockade type", "")
{
    m_effect = other.m_effect;
}

CardBlockade::~CardBlockade()
{
    delete m_effect;
}

// function which is called when we are printing the name of each card.
std::ostream& CardBlockade::write(std::ostream &os) const
{
    cout << m_effect;
    return os;
}

// **************** //
// Airlift functions:  //
// **************** //
Airlift::Airlift(Card::Effect* effect) : Order("Airlift type", "")
{
    m_effect = effect;
}

Airlift::Airlift(const Airlift& other) : Order("Airlift type", "")
{
    m_effect = other.m_effect;
}

Airlift::~Airlift()
{
    delete m_effect;
}

// function which is called when we are printing the name of each card.
std::ostream& Airlift::write(std::ostream &os) const
{
    cout << m_effect;
    return os;
}

// **************** //
// Diplomacy functions:  //
// **************** //
Diplomacy::Diplomacy(Card::Effect* effect) : Order("Diplomacy type", "")
{
    m_effect = effect;
}

Diplomacy::Diplomacy(const Diplomacy& other) : Order("Diplomacy type", "")
{
    m_effect = other.m_effect;
}

Diplomacy::~Diplomacy()
{
    delete m_effect;
}

// function which is called when we are printing the name of each card.
std::ostream& Diplomacy::write(std::ostream &os) const
{
    cout << m_effect;
    return os;
}



// **************** //
// Deck functions:  //
// **************** //

Deck::Deck() {//default
    m_cards= vector<Card*>();
    //srand(time(0));
}

Deck::Deck(int size)
{
    initialize(size);
}

//Function responsible for initializing the deck of playing cards to the given size.
void Deck::initialize(int size)
{
    for(int i=0; i < size; i++)
    {
        int randomNumber = rand() % 5;      //Random number within the type of cards
        // Notes from Noah: randomNumber is not truly random: https://tinyurl.com/8m37ewu3

        Card::Effect* effect = new Card::Effect(static_cast<Card::Effect>(randomNumber));    //Create the card
        switch (*effect)
        {
            case Card::Effect::BOMB:
                m_cards.push_back(new CardBomb(effect));
                break;
            case Card::Effect::REINFORCEMENT:
                m_cards.push_back(new Reinforcement(effect));
                break;
            case Card::Effect::BLOCKADE:
                m_cards.push_back(new CardBlockade(effect));
                break;
            case Card::Effect::AIRLIFT:
                m_cards.push_back(new Airlift(effect));
                break;
            case Card::Effect::DIPLOMACY:
                m_cards.push_back(new Diplomacy(effect));
                break;
        }
    }

    //Checks if the deck is valid before continuing
    while (!validate(m_cards))
    {
        initialize(size);
    }
}

Deck::Deck(const Deck& other){
    m_cards = other.m_cards;
}

Deck::~Deck()
{
    m_cards.clear();
}

// Ensures that when the deck is generated, that there is exactly one of each type of card
bool Deck::validate(vector<Card*> cards)
{
    // Create an array with an index for each possible card value
    int sum[5] = {};
    for(Card* card: cards)
    {
        // Convert the cards effect enum to an int, then increment the value at that index
        sum[static_cast<int>(*card->getEffect())] += 1;
    }

    // Display the amount of each type of card in the deck
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

// Counts how many cards are currently in the deck, and displays which effect they have.
void Deck::showDeck()
{
    int count = 1;
    cout << "\nThe deck currently contains:\n";
    for(Card* i: m_cards)
    {
        std::cout << count++ << ": " << i << "\n";
    }
    cout << "\n";
}

//Takes a card from the deck and places it in the players list of cards
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

// Returns the given card to the deck.
void Deck::returnCard(Card* card)
{
    m_cards.insert(m_cards.begin(), card);
}
vector<Card*> Deck::getDeckCards() {
    return m_cards;
}

std::ostream& operator<<(std::ostream& lhs, Deck& deck)
{
    int count = 1;
    cout << "\nThe deck currently contains:\n";
    for(Card* i: deck.m_cards)
    {
        std::cout << count++ << ": " << i << "\n";
    }
    return lhs;
}

Deck& Deck::operator=(const Deck& rhs)
{
    if(this == &rhs)
        return *this;

    m_cards = rhs.m_cards;
    return *this;
}

// **************** //
// Hand functions:  //
// **************** //
Hand::Hand()
{
}
Hand::Hand(Deck* hDeck) {
    m_cards=hDeck->getDeckCards();
}

Hand::Hand(const Hand& other)
{
    m_cards = other.m_cards;
}

Hand::~Hand()
{
    for (auto p : m_cards) delete p;
    m_cards.clear();
}


std::vector<Card*> Hand::getCards()
{
    return m_cards;
}

// Adds a card to the players hand
void Hand::drawCard(Card* card)
{
    m_cards.push_back(card);
}

// Prints out all the cards in a given players hand
void Hand::showCards()
{
    for(Card* c: m_cards)
    {
        std::cout << c << "\n";
    }

}

//Gets the last cast in the users hand and plays that one.
Card* Hand::useLast()
{
    Card* toUse = m_cards.back();
    m_cards.pop_back();
    return toUse;
}
// Note from Noah TODO: Add a way to use any card from hand, not just the last one


std::ostream& operator<<(std::ostream& lhs, Hand& hand)
{
    for(Card* i: hand.getCards())
    {
        std::cout << i << " card\n";
    }
    return lhs;
}

Hand& Hand::operator=(const Hand& rhs)
{
    if(this == &rhs)
        return *this;

    m_cards = rhs.m_cards;
    return *this;
}