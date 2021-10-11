#include<iostream>
#include<string>
#include"Card.h"
using namespace std;


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

void Card::play(Player& player, Deck& deck)
{
    //TODO: check with alexandre
    player.issueOrder(reinterpret_cast<const char *>(m_effect), "");
    deck.returnCard(this);
    cout << "\n" << m_effect << " was played by " << player.getName() << "\n";
}

Card::Effect* Card::getEffect()
{
    return m_effect;
}

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

Card& Card::operator=(const Card& rhs)
{
    if(this == &rhs)
        return *this;

    m_effect = rhs.m_effect;

    return *this;
}

// **************** //
// Bomb functions:  //
// **************** //
CardBomb::CardBomb(Card::Effect effect)
{
    m_effect = new Card::Effect(effect);
}
CardBomb::~CardBomb()
{
    delete m_effect;
}

std::ostream& CardBomb::write(std::ostream &os) const
{
    cout << m_effect;
    return os;
}

// **************** //
// Reinforcement functions:  //
// **************** //
Reinforcement::Reinforcement(Card::Effect effect)
{
    m_effect = new Card::Effect(effect);
}
Reinforcement::~Reinforcement()
{
    delete m_effect;
}

std::ostream& Reinforcement::write(std::ostream &os) const
{
    cout << m_effect;
    return os;
}

// **************** //
// Blockade functions:  //
// **************** //
CardBlockade::CardBlockade(Card::Effect effect)
{
    m_effect = new Card::Effect(effect);
}
CardBlockade::~CardBlockade()
{
    delete m_effect;
}

std::ostream& CardBlockade::write(std::ostream &os) const
{
    cout << m_effect;
    return os;
}

// **************** //
// Airlift functions:  //
// **************** //
Airlift::Airlift(Card::Effect effect)
{
    m_effect = new Card::Effect(effect);
}
Airlift::~Airlift()
{
    delete m_effect;
}

std::ostream& Airlift::write(std::ostream &os) const
{
    cout << m_effect;
    return os;
}

// **************** //
// Diplomacy functions:  //
// **************** //
Diplomacy::Diplomacy(Card::Effect effect)
{
    m_effect = new Card::Effect(effect);
}
Diplomacy::~Diplomacy()
{
    delete m_effect;
}

std::ostream& Diplomacy::write(std::ostream &os) const
{
    cout << m_effect;
    return os;
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
        switch (card)
        {
            case Card::Effect::BOMB:
                m_cards.push_back(new CardBomb(card));
                break;
            case Card::Effect::REINFORCEMENT:
                m_cards.push_back(new Reinforcement(card));
                break;
            case Card::Effect::BLOCKADE:
                m_cards.push_back(new CardBlockade(card));
                break;
            case Card::Effect::AIRLIFT:
                m_cards.push_back(new Airlift(card));
                break;
            case Card::Effect::DIPLOMACY:
                m_cards.push_back(new Diplomacy(card));
                break;
        }
    }

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
    cout << "\n";
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
    m_cards.insert(m_cards.begin(), card);
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
Hand::Hand(/* args */)
{
}

Hand::Hand(const Hand& other)
{
    m_cards = other.m_cards;
}

Hand::~Hand()
{
    m_cards.clear();
}
std::vector<Card*> Hand::getCards()
{
    return m_cards;
}

void Hand::drawCard(Card* card)
{
    m_cards.push_back(card);
}
void Hand::showCards(Player player)
{
    cout << "\nPlayer: " << player.getName() << " currently has the following cards\n";
    for(Card* c: m_cards)
    {
        std::cout << c << "\n";
    }

}
Card* Hand::useLast()
{
    Card* toUse = m_cards.back();
    m_cards.pop_back();
    return toUse;
}

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
