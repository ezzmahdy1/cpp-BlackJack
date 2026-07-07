#include"funct.h"
using namespace std;





void shuffle_deck(card* deck) {
    for (int i = 51;i > 0;i--) {
        int j = rand() % (i + 1);
        card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }

}


void fill_Q(string sym, order symbol_char, card* deck) {
    string nn;
    int true_n;
    for (int i = 13 * (symbol_char - 1);i < 13 * symbol_char;i++) {

        switch (i) {                                 
        case 0:
            nn = "A";
            true_n = 11;
            break;
        case 13:
            nn = "A";
            true_n = 11;
            break;
        case 26:
            nn = "A";
            true_n = 11;
            break;
        case 39:
            nn = "A";
            true_n = 11;
            break;
        case 1:
            nn = "J";
            true_n = 10;
            break;
        case 14:
            nn = "J";
            true_n = 10;
            break;
        case 27:
            nn = "J";
            true_n = 10;
            break;
        case 40:
            nn = "J";
            true_n = 10;
            break;
        case 11:
            nn = "K";
            true_n = 10;
            break;
        case 24:
            nn = "K";
            true_n = 10;
            break;
        case 37:
            nn = "K";
            true_n = 10;
            break;
        case 50:
            nn = "K";
            true_n = 10;
            break;
        case 12:
            nn = "Q";
            true_n = 10;
            break;
        case 25:
            nn = "Q";
            true_n = 10;
            break;
        case 38:
            nn = "Q";
            true_n = 10;
            break;
        case 51:
            nn = "Q";
            true_n = 10;
            break;

        }
        if (i > 1 && i < 11) {
            nn = to_string(i);
            true_n = i;
        }
        if (i > 14 && i < 24) {
            nn = to_string(i - 13);
            true_n = i - 13;
        }
        if (i > 27 && i < 37) {
            nn = to_string(i - 26);
            true_n = i - 26;
        }
        if (i > 40 && i < 50) {
            nn = to_string(i - 39);
            true_n = i - 39;
        }
        deck[i] = card(sym, nn, true_n);
    }
}


void fill_deck(card* deck) {
    fill_Q("♠", s, deck);
    fill_Q("♥", h, deck);
    fill_Q("♦", d, deck);
    fill_Q("♣", c, deck);
}
