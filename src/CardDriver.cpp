#include <iostream>
#include "Card.h"

using namespace std;

int main(int args, char *argv[]) {
    // cout << "Initializing the deck\n";
    Deck deck(30);
    deck.showDeck();

    // cout << "\nInitializing players: \n";
    Player p1("Alexander");
    deck.draw(p1);
    deck.draw(p1);
    deck.draw(p1);

    // Show that the cards have gone into the players hands
    cout << "\n" << p1.getName() << " currently has the following cards in his hand:\n";
    p1.getHand()->showCards();

    // // Show that the cards have been removed from the deck
    cout << deck;

    // Use the last card in the players hand
    p1.getHand()->useLast()->play(p1, deck);

    // Show that an order has been created
    p1.printOrders();

    // Show that the card has been removed from the players hand
    cout << "\n" << p1.getName() << " currently has the following cards in his hand:\n";
    p1.getHand()->showCards();

    // Show that the deck has the card that was played
    cout << deck;

    // Removing the last two cards.
    p1.getHand()->useLast()->play(p1, deck);
    p1.getHand()->useLast()->play(p1, deck);
    p1.printOrders();
    cout << deck;

    int i;
    cin >> i;

    return 0;
}