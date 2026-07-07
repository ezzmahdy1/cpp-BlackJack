#include<iostream>
#include<windows.h>
#include <ctime>
#include<vector>
#include<algorithm>
#include<type_traits>
#include "cards.h"
#include "funct.h"
using namespace std;  //symbols ♠(s)  ♥(h)  ♦(d)  ♣(c)
enum signs { K = 10, A = 11, J = 10, Q = 10 };


int main() {
    srand(time(0));
    SetConsoleOutputCP(65001);
    card deck[52];
    hand player;
    hand dealer;
    player.is_player = true;
    fill_deck(deck);

    int bet;
    int n = 1;  //number of rounds
    int i = 0;  //index of deck
    bool loop_1 = true;
    bool loop_2 = true;

    int balance = 100000;

    cout << "================== welcome =======================" << endl;
    while (loop_1 == true) {
        shuffle_deck(deck);
        cout << "================== " << "round " << n << " =======================" << endl;
        cout << "======= Enter your bet (" << balance << "  owned) ===========" << endl;
        cin >> bet;
        while (bet > balance) {
            cout << "insufficient funds enter new bet:" << endl;
            cin >> bet;
        }
        balance = balance - bet;

        cout << "\033[2J\033[H";
        dealer.draw_card(deck, i, 2);
        dealer.cards[0].hide = true;

        dealer.print_table();

        dealer.sc = dealer.score();
        if (dealer.sc == 21) {
            dealer.cards[0].hide = false;
            dealer.print_table();
            cout << endl << "the dealer has black jack !!" << endl;
        }
        else {

            player.draw_card(deck, i, 2);

            player.print_table();

            player.sc = player.score();
            cout << "your score is " << player.sc << endl;
            if (player.sc == 21) {
                cout << endl << "the player has black jack !!" << endl;
                balance = balance + (3 * bet / 2) + bet;
                cout << "your new balance is " << balance << endl;
            }
            else {
                player.player_move(balance, bet, deck, i, player, dealer);

                if (player.is_bust == false) {
                    dealer.dealer_move(deck, player, dealer, i, balance, bet);
                    if (dealer.is_bust == false) {
                        if (player.sc > dealer.sc) {
                            cout << "you won !!" << endl;
                            balance = balance + (2 * bet);
                            cout << "your new balance is " << balance << endl;
                        }
                        else if (player.sc == dealer.sc) {
                            cout << "tie !!" << endl;
                            balance = balance + bet;
                            cout << "your balance remain unchanged" << endl;
                        }
                        else {
                            cout << "the dealer won" << endl;
                        }
                    }
                }

            }

        }

        char y_n = 'b';
        if (balance == 0) {
            cout << "you are bankrupt :(" << endl;
            return 0;
        }
        cout << "wanna proceed with next round? (y/n)" << endl;
        while (!(y_n == 'y' || y_n == 'n') == true) {
            cin >> y_n;
            if (!(y_n == 'y' || y_n == 'n') == true)
                cout << "please select a valid option";
        }

        if (y_n == 'y') {
            n++;
            bet = 0;
            cout << "\033[2J\033[H";
            i = 0;
            player.restart();
            dealer.restart();

        }
        else
            return 0;




    }



}
