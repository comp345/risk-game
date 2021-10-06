#pragma once
#include<vector>
#include<string>
class Player;
class Deck;

using namespace std;

class Card
{
public:
    enum class Effect {bomb, reinforcement, blockade, airlift, diplomacy};

    //Constructors
    Card(Effect m_effect);
    Card(const Card& other);
    ~Card();

    // Methods
    void play(Player& player, Deck& deck);
    Effect* getEffect();

    // Operator functions
    friend std::ostream& operator<<(std::ostream& lhs, Card* c);
    friend std::ostream& operator<<(std::ostream& lhs, Effect* e);
    Card& operator=(const Card& rhs);

private:
    Effect* m_effect;

};




class Deck
{
private:
    std::vector<Card*> m_cards;

public:
    //Constructors
    Deck(int size);
    Deck(const Deck& other);
    ~Deck();

    // Functions
    void initialize(int size);
    bool validate(vector<Card*> cards);
    void showDeck();
    void draw(Player& player);
    void returnCard(Card* card);

    // Operator functions
    friend std::ostream& operator<<(std::ostream& lhs, Deck& d);
    Deck& operator=(const Deck& rhs);

};


class Hand
{
private:
    std::vector<Card*> m_cards;
public:
    //Constructors
    Hand(/* args */);
    Hand(const Hand& other);
    ~Hand();

    // Functions
    void drawCard(Card* card);
    void showCards(Player player);
    Card* useLast();

    // Operator functions
    friend std::ostream& operator<<(std::ostream& lhs, Deck& d);
    Deck& operator=(const Deck& rhs);
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


