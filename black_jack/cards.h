#pragma once
#include <iostream>
#include<windows.h>
#include <ctime>
#include<vector>
#include<string>
#include <map>
using namespace std;


class card;  //the card class that contains card attributes like the symbol and number etc.
class hand;  //the hand class that contains the attributes of the hand and methods like the cards and drawing a card 

void print_table_whole(hand& player, hand& dealer);  //the function that prints the table and its contents

class card {
public:
    string symbol; //the symbol of the card object heart,spade,etc.
    string no;     //the number or sign of card object 1,4,K,Q,etc. 
    int t_n;       //the true number that the score depends on when calculating
    bool hide;     //the state of a card wheather its hidden or not
    card() {       //default constructur (empty card)
    }
    card(string Symbol, string no_or_sign, int true_no) {   //the construcor used to describe a card
        symbol = Symbol;
        no = no_or_sign;
        t_n = true_no;
    }
};

class hand {
public:
    vector <card> cards;        //the cards contained in a hand
    string spaces = "                                          ";       //the spaces used in printing the table
    int index_hand = 0;     //the index of the cards vector
    int sc;                 //the value of the score achieved by a hand
    int no_c;               //the number of cards in a hand
    bool is_player = false; //the state determining wheather the hand is a player's or not 
    bool is_bust = false;   //the state determining wheather the hand is bust or not
    int n = 0;              //the no. rounds played by a hand

    void draw_card(card* deck, int& index_deck, int no = 1);    //the function that draws a card from deck to hand
    void print_card(int i = 0, bool hidden = false);            //the function that prints a card from hand
    int score();                                                //the function that determine the score
    void print_table();                                         //the function that helps print the table at the start of a round
    void player_move(int& balance, int& bet, card* deck, int& index_deck, hand& player, hand& dealer);//the function passing player moves
    void dealer_move(card* deck, hand& player, hand& dealer, int& index_deck, int& balance, int& bet);//the function passing cpu moves
    void restart();//the function that restarts the hand objects in case of new round


};