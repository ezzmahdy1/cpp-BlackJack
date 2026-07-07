#include"cards.h"
#include<iostream>
#include<windows.h>
#include <ctime>
#include<vector>
using namespace std;


void hand::draw_card(card* deck, int& index_deck, int no) {
    for (int n = 1;n <= no;n++) {
        cards.push_back(deck[index_deck]);
        index_deck++;
        index_hand++;
    }
}

void hand::print_card(int i, bool hidden) {
    if (hidden == true) {
        cout << spaces << "┌────┐" << endl;
        cout << spaces << "│    │" << endl;
        cout << spaces << "│    │" << endl;
        cout << spaces << "│    │" << endl;
        cout << spaces << "└────┘";
        return;
    }
    if (cards.at(i).no == "10") {
        cout << spaces << "┌────┐" << endl;
        cout << spaces << "│" << cards.at(i).no << cards.at(i).symbol << " │" << endl;
        cout << spaces << "│    │" << endl;
        cout << spaces << "│ " << cards.at(i).symbol << cards.at(i).no << "│" << endl;
        cout << spaces << "└────┘";
        return;
    }
    cout << spaces << "┌────┐" << endl;
    cout << spaces << "│" << cards.at(i).no << cards.at(i).symbol << "  │" << endl;
    cout << spaces << "│    │" << endl;
    cout << spaces << "│  " << cards.at(i).symbol << cards.at(i).no << "│" << endl;
    cout << spaces << "└────┘";
}

int hand::score() {
    no_c = cards.size();
    int no_a = 0;
    int score = 0;
    for (int i = 0;i < no_c;i++) {
        if (cards.at(i).no == "A") {
            no_a++;
        }
    }
    if (no_a > 0) {
        for (int j = 0;j < no_c;j++) {
            score = score + cards.at(j).t_n;
        }
        if (score > 21) {
            if (no_a > 1) {
                score = score - 10 * (no_a - 1);
            }
            if (score > 21) {
                score = score - 10;
            }
        }
    }
    else {
        for (int z = 0;z < no_c;z++) {
            score = score + cards.at(z).t_n;
        }
    }
    return score;
}

void hand::print_table() {
    spaces = "                                          ";
    no_c = cards.size();
    if (is_player == false)
        cout << "================ dealer's hand ====================" << endl;
    else
        cout << "================ player's hand ====================" << endl;
    for (int jj = 0;jj < no_c;jj++) {
        print_card(jj, cards[jj].hide);
        cout << "\033[4A" << "\r";
        for (int ii = 0;ii <= 3;ii++) {
            spaces.pop_back();
        }
    }
    cout << endl << endl << endl << endl << endl;
}

void hand::player_move(int& balance, int& bet, card* deck, int& index_deck, hand& player, hand& dealer) {
    int move;
    if (n < 1) {
        cout << "whats your move Hit (1)|stand (2)|Doubledown (3) ";
        cin >> move;
        if (move == 2) {
            return;
        }
        if (move == 3) {
            balance = balance - bet;
            bet = 2 * bet;
            draw_card(deck, index_deck);
            print_table_whole(player, dealer);

            sc = score();
            cout << "your score is " << player.sc << endl;
            if (sc > 21) {
                is_bust = true;
                cout << "\033[2J\033[H";
                cards[0].hide = false;
                print_table_whole(player, dealer);
                cout << "you are bust !!" << endl;
                return;

            }

            return;
        }
        if (move == 1) {
            cout << "\033[2J\033[H";
            draw_card(deck, index_deck);
            print_table_whole(player, dealer);

            sc = score();
            cout << "your score is " << player.sc << endl;
            if (sc < 21) {
                n = n + 1;
                player_move(balance, bet, deck, index_deck, player, dealer);
            }
            else if (sc == 21) {
                cout << "you got 21 !!" << endl;
                return;
            }
            else {
                cout << "you are bust !!" << endl;
                is_bust = true;
                return;
            }


        }
    }
    else {
        cout << "whats your move Hit (1)|stand (2)";
        cin >> move;

        if (move == 2) {
            return;
        }
        if (move == 1) {
            cout << "\033[2J\033[H";
            draw_card(deck, index_deck);
            print_table_whole(player, dealer);

            sc = score();
            cout << "your score is " << player.sc << endl;
            if (sc < 21) {
                player_move(balance, bet, deck, index_deck, player, dealer);
            }
            else if (sc == 21) {
                cout << "you got 21 !!" << endl;
                return;
            }
            else {
                is_bust = true;
                cout << "you are bust !!" << endl;
                return;
            }
        }
    }
}

void hand::dealer_move(card* deck, hand& player, hand& dealer, int& index_deck, int& balance, int& bet) {
    cout << "\033[2J\033[H";
    cards[0].hide = false;
    print_table_whole(player, dealer);
    Sleep(2500);
    sc = score();
    if (sc < 17) {
        cout << "\033[2J\033[H";
        draw_card(deck, index_deck);
        print_table_whole(player, dealer);
        sc = score();

        if (sc < 17) {
            if (sc < player.sc)
                dealer_move(deck, player, dealer, index_deck, balance, bet);
            else
                return;
        }
        else if (sc > 21) {
            cout << "the dealer is bust !!" << endl;
            is_bust = true;
            balance = balance + (2 * bet);
            cout << "your new balance is " << balance << endl;
            return;
        }
        else {
            return;
        }
    }
}

void hand::restart() {
    cards.clear();
    spaces = "                                          ";
    index_hand = 0;
    sc = 0;
    no_c = 0;
    is_bust = false;
    n = 0;
}



void print_table_whole(hand& player, hand& dealer) {
    player.spaces = "                                          ";
    dealer.spaces = "                                          ";
    player.no_c = player.cards.size();
    dealer.no_c = dealer.cards.size();
    //cout<<no_c;
    cout << "================ dealer's hand ====================" << endl;
    for (int zz = 0;zz < dealer.no_c;zz++) {
        dealer.print_card(zz, dealer.cards[zz].hide);
        cout << "\033[4A" << "\r";
        for (int mm = 0;mm <= 3;mm++) {
            dealer.spaces.pop_back();
        }
    }
    cout << endl << endl << endl << endl << endl;
    cout << "================ player's hand ====================" << endl;

    for (int jj = 0;jj < player.no_c;jj++) {
        player.print_card(jj, player.cards[jj].hide);
        cout << "\033[4A" << "\r";
        for (int ii = 0;ii <= 3;ii++) {
            player.spaces.pop_back();
        }
    }
    cout << endl << endl << endl << endl << endl;
    cout << "your score is " << player.sc << endl;
}