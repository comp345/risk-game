#pragma once
#include<vector>
#include<string>
class Player;
class Deck;

using namespace std;
// correct copy constructor, assignment operator, and stream insertion operator
class Card
{
public:
    enum class Effect {bomb, reinforcement, blockade, airlift, diplomacy};

    Card(Effect m_effect);
    ~Card();

    // Methods
    void play(Player& player, Deck& deck);
    
    // Operator functions
    friend std::ostream& operator<<(std::ostream& lhs, Card* c);
    friend std::ostream& operator<<(std::ostream& lhs, Effect* e);

    Effect* getEffect();
private:
    Effect* m_effect;

};




class Deck
{
private:
    std::vector<Card*> m_cards;

public:
    Deck(int size);
    ~Deck();

    // Functions
    void initialize(int size);
    bool validate(vector<Card*> cards);
    void showDeck();
    void draw(Player& player);
    void returnCard(Card* card);

};


class Hand
{
private:
    std::vector<Card*> m_cards;
public:
    Hand(/* args */);
    ~Hand();

    void drawCard(Card* card);
    void showCards(Player player);
    Card* useLast();
};





class Player
{
private:
    std::string m_name;
    Hand* m_hand;
    std::vector<int> m_orders;

public:
    Player(std::string name);

    // Methods
    void add_to_orders(int value);
    void showOrders();

    // Getters
    std::string getName();
    Hand* getHand();

    ~Player();
};


