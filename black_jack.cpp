#include<iostream>
#include<windows.h>
#include <ctime>
#include<vector>
using namespace std;  //symbols ♠(s)  ♥(h)  ♦(d)  ♣(c)
enum order {s=1,h=2,d=3,c=4};
enum signs {K=10,A=11,J=10,Q=10};

class hand;
class card;


void print_table_whole(hand &player,hand &dealer);

class card {
    public:
        string symbol;
        string no;
        int t_n;
        bool hide;
        card(){

        }
        card (string Symbol,string no_or_sign,int true_no){
        symbol=Symbol;
        no=no_or_sign;
        t_n=true_no;
        }
        

};

class hand{
    public:
        vector <card> cards ;
        string spaces="                                          ";
        int index_hand=0;
        int sc;
        int no_c;
        bool is_player=false;
        bool is_bust=false;
        int n=0;

        void draw_card(card *deck,int &index_deck,int no=1){
            for(int n=1;n<=no;n++){
                cards.push_back(deck[index_deck]);
                /*cards[0].hide=true;
                print_card(index_hand,cards[index_hand].hide);
                for(int ii=0;ii<=3;ii++){
                    spaces.pop_back();
                }*/
                
                index_deck++;
                index_hand++;
                
            }


        }
        void print_card(int i=0,bool hidden=false){
        if(hidden==true){
            cout<<spaces<<"┌────┐"<<endl;
            cout<<spaces<<"│    │"<<endl;
            cout<<spaces<<"│    │"<<endl; 
            cout<<spaces<<"│    │"<<endl;
            cout<<spaces<<"└────┘";
            return;
        }
        if (cards.at(i).no=="10"){
            cout<<spaces<<"┌────┐"<<endl;
            cout<<spaces<<"│"<<cards.at(i).no<<cards.at(i).symbol<<" │"<<endl;
            cout<<spaces<<"│    │"<<endl; 
            cout<<spaces<<"│ "<<cards.at(i).symbol<<cards.at(i).no<<"│"<<endl;
            cout<<spaces<<"└────┘";
            return;
        }
        cout<<spaces<<"┌────┐"<<endl;
        cout<<spaces<<"│"<<cards.at(i).no<<cards.at(i).symbol<<"  │"<<endl;
        cout<<spaces<<"│    │"<<endl; 
        cout<<spaces<<"│  "<<cards.at(i).symbol<<cards.at(i).no<<"│"<<endl;
        cout<<spaces<<"└────┘";
        }

        int score (){
            no_c=cards.size();
            int no_a=0;
            int score=0;
            for(int i=0;i<no_c;i++){
                if (cards.at(i).no=="A"){
                    no_a++;
                }
            }
            if(no_a>0){
                for (int j=0;j<no_c;j++){
                    score=score+cards.at(j).t_n;
                }
                if(score>21){
                    if(no_a>1){
                        score=score-10*(no_a-1);
                    }
                    if(score>21){
                        score=score-10;
                    }
                        
                }
                

            }
            else{
                for (int z=0;z<no_c;z++){
                    score=score+cards.at(z).t_n;
                }
                
            }
            return score;
        }

        void print_table(){
            spaces="                                          ";
            no_c=cards.size();
            //cout<<no_c;
            if(is_player==false)
                cout<<"================ dealer's hand ===================="<<endl;
            else 
                cout<<"================ player's hand ===================="<<endl;
            for(int jj=0;jj<no_c;jj++){
                print_card(jj,cards[jj].hide);
                cout<<"\033[4A"<<"\r";
                for(int ii=0;ii<=3;ii++){
                    spaces.pop_back();
                }
                
                
                
            }
            
            cout<<endl<<endl<<endl<<endl<<endl;

        }

        void player_move(int &balance,int &bet,card *deck,int &index_deck,hand &player,hand &dealer){
            int move;
            if(n<1){
                cout <<"whats your move Hit (1)|stand (2)|Doubledown (3) ";
                cin>>move;

                if(move==2){
                    return;
                }
                if (move==3){
                    balance=balance-bet;
                    bet=2*bet;
                    draw_card(deck,index_deck);
                    print_table_whole(player,dealer);
                    
                    sc=score();
                    cout<<"your score is "<<player.sc<<endl;
                    if(sc>21){
                        is_bust=true;
                        cout << "\033[2J\033[H";
                        cards[0].hide=false;
                        print_table_whole(player,dealer);
                        cout<<"you are bust !!"<<endl;
                        return;

                    }

                    return;
                }
                if (move==1){
                    cout << "\033[2J\033[H";
                    draw_card(deck,index_deck);
                    print_table_whole(player,dealer);
                    
                    sc=score();
                    cout<<"your score is "<<player.sc<<endl;
                    if(sc<21){
                        n=n+1;
                        player_move(balance,bet,deck,index_deck,player,dealer);
                    }
                    else if(sc==21){
                        cout<<"you got 21 !!"<<endl;
                        return;
                    }
                    else{
                        cout<<"you are bust !!"<<endl;
                        is_bust=true;
                        return;
                    }

                
                }
            }
            else{
                cout <<"whats your move Hit (1)|stand (2)";
                cin>>move;

                if(move==2){
                    return;
                }
                if (move==1){
                    cout << "\033[2J\033[H";
                    draw_card(deck,index_deck);
                    print_table_whole(player,dealer);
                    
                    sc=score();
                    cout<<"your score is "<<player.sc<<endl;
                    if(sc<21){
                    player_move(balance,bet,deck,index_deck,player,dealer);
                    }
                    else if(sc==21){
                        cout<<"you got 21 !!"<<endl;
                        return;
                    }
                    else{
                        is_bust=true;
                        cout<<"you are bust !!"<<endl;
                        return;
                    }
            }

        }
    }

        void dealer_move(card *deck,hand &player,hand &dealer,int &index_deck,int &balance,int &bet){
            cout << "\033[2J\033[H";
            cards[0].hide=false;
            print_table_whole(player,dealer);
            Sleep(2500);
            sc=score();
            if(sc<17){
                cout << "\033[2J\033[H";
                draw_card(deck,index_deck);
                print_table_whole(player,dealer);
                sc=score();

                if(sc<17){
                    dealer_move(deck,player,dealer,index_deck,balance,bet);
                }
                else if(sc>21){
                    cout<<"the dealer is bust !!"<<endl;
                    is_bust=true; 
                    balance=balance+(2*bet);
                    cout<<"your new balance is "<<balance<<endl;
                    return;
                }
                else{
                    return;
                }
            }
        }
    
        void restart(){
            cards.clear();
            spaces="                                          ";
            index_hand=0;
            sc=0;
            no_c=0;
            is_bust=false;
            n=0;

        }

};



void fill_Q(string sym,order symbol_char,card *deck);

void fill_deck(card *deck);

void shuffle_deck(card *deck);


bool bj(int score);

bool bust(int t_n_new,int old_score);
bool r_21(int t_n_new,int old_score);

int main(){
    srand(time(0));
    SetConsoleOutputCP(65001);
    card deck[52];
    hand player;
    hand dealer;
    player.is_player=true;
    fill_deck(deck);    
    
    int bet;
    int n=1;  //number of rounds
    int i=0;  //index of deck
    bool loop_1=true;
    bool loop_2=true;

    int balance=100000;
    
    cout <<"================== welcome ======================="<<endl;
    while(loop_1==true){
        shuffle_deck(deck);
        cout <<"================== "<<"round "<<n<<" ======================="<<endl;
        cout <<"======= Enter your bet ("<<balance<<"  owned) ==========="<<endl;
        cin>>bet;
        while(bet>balance){
            cout<<"insufficient funds enter new bet:"<<endl;
            cin>>bet;
        }
        balance=balance-bet;

        cout << "\033[2J\033[H";
        dealer.draw_card(deck,i,2);
        dealer.cards[0].hide=true;
        
        dealer.print_table();
        
        dealer.sc=dealer.score();
        if(dealer.sc==21){
            dealer.cards[0].hide=false;
            dealer.print_table();
            cout <<endl<<"the dealer has black jack !!"<<endl;
        }
        else{
            
            player.draw_card(deck,i,2);
            
            player.print_table();

            player.sc=player.score();
            cout<<"your score is "<<player.sc;
            cout<<endl;
            if(player.sc==21){
                cout <<endl<<"the player has black jack !!"<<endl;
                balance=balance+(3*bet/2)+bet;
                cout<<"your new balance is "<<balance<<endl;
            }
            else{
                player.player_move(balance,bet,deck,i,player,dealer);
                //print_table_whole(player,dealer);
                if (player.is_bust==false){
                    dealer.dealer_move(deck,player,dealer,i,balance,bet);
                    if(dealer.is_bust==false){
                        if(player.sc>dealer.sc){
                            cout<<"you won !!"<<endl;
                            balance=balance+(2*bet);
                            cout<<"your new balance is "<<balance<<endl;
                        }
                        else if(player.sc==dealer.sc){
                            cout<<"tie !!"<<endl;
                            balance=balance+bet;
                            cout<<"your balance remain unchanged"<<endl;
                        }
                        else{
                            cout<<"the dealer won"<<endl;
                        }
                    }
                }
                    
            }
            
        }

        char y_n='b';
            if(balance==0){
                cout<<"you are bankrupt :("<<endl;
                return 0;
            }
            cout<<"wanna proceed with next round? (y/n)"<<endl;
            cin>>y_n;
            
            if(y_n=='y'){
                n++;
                bet=0;
                cout << "\033[2J\033[H";
                i=0;
                player.restart();
                dealer.restart();
                
            }
            else
                return 0;



    
    }
         


}

void print_table_whole(hand &player,hand &dealer){
    player.spaces="                                          ";
    dealer.spaces="                                          ";
    player.no_c=player.cards.size();
    dealer.no_c=dealer.cards.size();
    //cout<<no_c;
    cout<<"================ dealer's hand ===================="<<endl;
    for(int zz=0;zz<dealer.no_c;zz++){
        dealer.print_card(zz,dealer.cards[zz].hide);
        cout<<"\033[4A"<<"\r";
        for(int mm=0;mm<=3;mm++){
            dealer.spaces.pop_back();
        }
    }
    cout<<endl<<endl<<endl<<endl<<endl;
    cout<<"================ player's hand ===================="<<endl;
    
    for(int jj=0;jj<player.no_c;jj++){
        player.print_card(jj,player.cards[jj].hide);
        cout<<"\033[4A"<<"\r";
        for(int ii=0;ii<=3;ii++){
            player.spaces.pop_back();
        }
    }
    cout<<endl<<endl<<endl<<endl<<endl;
    cout<<"your score is "<<player.sc<<endl;
}







void shuffle_deck(card *deck){
    for (int i=51;i>0;i--){
        int j=rand()%(i+1);
        card temp = deck[i];
        deck[i]=deck[j];
        deck[j]=temp;
    }

}



void fill_Q(string sym,order symbol_char,card *deck){
            string nn;
            int true_n;
            for (int i=13*(symbol_char-1);i<13*symbol_char;i++){
                
                switch(i){                     //             
                    case 0:
                        nn="A";
                        true_n=11;
                        break;
                    case 13:
                        nn="A";
                        true_n=11;
                        break;
                    case 26:
                        nn="A";
                        true_n=11;
                        break;
                    case 39:
                        nn="A";
                        true_n=11;
                        break;
                    case 1:
                        nn="J";
                        true_n=10;
                        break;
                    case 14:
                        nn="J";
                        true_n=10;
                        break;
                    case 27:
                        nn="J";
                        true_n=10;
                        break;
                    case 40:
                        nn="J";
                        true_n=10;
                        break;
                    case 11:
                        nn="K";
                        true_n=10;
                        break;
                    case 24:
                        nn="K";
                        true_n=10;
                        break;
                    case 37:
                        nn="K";
                        true_n=10;
                        break;
                    case 50:
                        nn="K";
                        true_n=10;
                        break;
                    case 12:
                        nn="Q";
                        true_n=10;
                        break;
                    case 25:
                        nn="Q";
                        true_n=10;
                        break;
                    case 38:
                        nn="Q";
                        true_n=10;
                        break;
                    case 51:
                        nn="Q";
                        true_n=10;
                        break;
                       
                }
                if(i>1&&i<11){
                    nn=to_string(i);
                    true_n=i;
                }
                if(i>14&&i<24){
                    nn=to_string(i-13);
                    true_n=i-13;
                }
                if(i>27&&i<37){
                    nn=to_string(i-26);
                    true_n=i-26;
                }
                if(i>40&&i<50){
                    nn=to_string(i-39);
                    true_n=i-39;
                }
                deck [i]=card (sym,nn,true_n);
            }
        }

void fill_deck(card *deck){
    fill_Q("♠",s,deck);    
    fill_Q("♥",h,deck);    
    fill_Q("♦",d,deck);    
    fill_Q("♣",c,deck);  
}


