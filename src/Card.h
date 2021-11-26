#pragma once
#include <vector>
#include <string>
// #include "Player.h"
#include "LoggingObserver.h"
#include "Orders.h"


class Deck;
class Hand;
class Player;

using namespace std;

// Helper functions
void initializedRand();

// Original declarations from A1

class Card : virtual public Order
{
public:
    enum class Effect {
        BOMB, REINFORCEMENT, BLOCKADE, AIRLIFT, DIPLOMACY
    };

    //Constructors
    Card(Effect m_effect);

    Card(const Card &other);

    Card();

    ~Card();

    // Methods
    void play(Player &player, Deck &deck);

    Effect *getEffect();

    bool validate ();
    bool execute ();

    virtual std::ostream &write(std::ostream &os) const;

    // Operator functions
    friend std::ostream &operator<<(std::ostream &lhs, Card *c);

    friend std::ostream &operator<<(std::ostream &lhs, Effect *e);

    Card &operator=(const Card &rhs);

protected:
    Effect *m_effect;

};


class CardBomb : virtual public Card {
private:

public:
    CardBomb(Effect* effect);
    CardBomb(const CardBomb &b);
    // CardBomb(Player *p, Territory * target);
    ~CardBomb();

    std::ostream &write(std::ostream &os) const;
};

class Reinforcement : virtual public Card {
private:

public:
    Reinforcement(Effect* effect);
    Reinforcement(const Reinforcement& reinforcement);
    ~Reinforcement();

    std::ostream &write(std::ostream &os) const;
};

class CardBlockade : virtual public Card {
private:

public:
    CardBlockade(Effect* effect);
    CardBlockade(const CardBlockade& blockade);
    ~CardBlockade();

    std::ostream &write(std::ostream &os) const;
};

class Airlift : virtual public Card {
private:

public:
    Airlift(Effect* effect);
    Airlift(const Airlift& airlift);
    ~Airlift();

    std::ostream &write(std::ostream &os) const;
};

class Diplomacy : virtual public Card {
private:

public:
    Diplomacy(Effect* effect);
    Diplomacy(const Diplomacy& diplomacy);
    ~Diplomacy();

    std::ostream &write(std::ostream &os) const;
};


class Deck {
private:
    std::vector<Card *> m_cards;

public:
    //Constructors
    Deck();

    Deck(int size);

    Deck(const Deck &other);

    ~Deck();

    // Functions
    void initialize(int size);

    bool validate(vector<Card *> cards);

    void showDeck();

    void draw(Player &player);

    void returnCard(Card *card);

    vector<Card*> getDeckCards();

    // Operator functions
    friend std::ostream &operator<<(std::ostream &lhs, Deck &d);

    Deck &operator=(const Deck &rhs);

};


class Hand {
private:
    std::vector<Card *> m_cards;

public:
    //Constructors
    Hand();

    Hand(Deck*);

    Hand(const Hand &other);

    ~Hand();

    std::vector<Card *> getCards();

    // Functions
    void drawCard(Card *card);

    void showCards();

    Card *useLast();

    // Operator functions
    friend std::ostream &operator<<(std::ostream &lhs, Deck &d);

    Hand &operator=(const Hand &rhs);
};