#pragma once
#include "cards.h"
using namespace std;

enum order { s = 1, h = 2, d = 3, c = 4 };//enumurator to help with variable conversion


void print_table_whole(hand& player, hand& dealer);//the function that prints the whole table (already in cards.h)

void fill_Q(string sym, order symbol_char, card* deck);//the function that fills quarter  of the deck

void fill_deck(card* deck);//the function that fills the whole deck

void shuffle_deck(card* deck);//the function that shuflle the deck 