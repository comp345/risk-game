#include <iostream>
#include "cards.h"
using namespace std;

int main(int args, char * argv[]) {
    // cout << "Initializing the deck\n";
    Deck deck(30);
    deck.showDeck();

    // cout << "\nInitializing players: \n";
    Player p1("Alexander");
    deck.draw(p1);
    deck.draw(p1);
    deck.draw(p1);

    // Show that the cards have gone into the players hands
    p1.getHand()->showCards(p1);

    // // Show that the cards have been removed from the deck
    cout << deck;

    // // Use the last card in the players hand
    p1.getHand()->useLast()->play(p1, deck);

    // // Show that an order has been created
    p1.showOrders();

    // // Show that the card has been removed from the players hand
    p1.getHand()->showCards(p1);

    // // Show that the deck has the card that was played
    cout << deck;

    // // Removing the last two cards.
    p1.getHand()->useLast()->play(p1, deck);
    p1.getHand()->useLast()->play(p1, deck);
    p1.showOrders();
    cout << deck;


    // Test inheritance
    // Bomb test(Card::Effect::BOMB);
    // cout << test << "\n";


    


    int i;
    cin >> i;

    return 0;
}


