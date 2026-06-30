#include<iostream>
#include<windows.h>
#include <ctime>
using namespace std;  //symbols ♠(s)  ♥(h)  ♦(d)  ♣(c)
enum order {s=1,h=2,d=3,c=4};
enum signs {K=10,A=11,J=10,Q=10};


class card {
        public:
          string symbol;
          string no;
          int t_n;
          card(){

          }
          card (string Symbol,string no_or_sign,int true_no){
            symbol=Symbol;
            no=no_or_sign;
            t_n=true_no;
          }
          void draw_card(string spaces="",bool hidden=false){
            if(hidden==true){
                cout<<spaces<<"┌────┐"<<endl;
                cout<<spaces<<"│    │"<<endl;
                cout<<spaces<<"│    │"<<endl; 
                cout<<spaces<<"│    │"<<endl;
                cout<<spaces<<"└────┘";
                return;
            }
            if (no=="10"){
                cout<<spaces<<"┌────┐"<<endl;
                cout<<spaces<<"│"<<no<<symbol<<" │"<<endl;
                cout<<spaces<<"│    │"<<endl; 
                cout<<spaces<<"│ "<<symbol<<no<<"│"<<endl;
                cout<<spaces<<"└────┘";
                return;
            }
            cout<<spaces<<"┌────┐"<<endl;
            cout<<spaces<<"│"<<no<<symbol<<"  │"<<endl;
            cout<<spaces<<"│    │"<<endl; 
            cout<<spaces<<"│  "<<symbol<<no<<"│"<<endl;
            cout<<spaces<<"└────┘";
          }

};

struct round_vars {
card *deck;
int c;
int n;
int score;
bool end;
string spaces="                                           ";
};

void fill_Q(string sym,order symbol_char,card *deck);

void fill_deck(card *deck);

void shuffle_deck(card *deck);

void player_move(round_vars &player);

void hit(round_vars &player);

bool bj(int score);

bool bust(int t_n_new,int old_score);
bool r_21(int t_n_new,int old_score);

int main(){
    srand(time(0));
    SetConsoleOutputCP(65001);
    card deck[52];
    fill_deck(deck);    
    
    int bet;
    int n=1;
    bool H=true;
    cout << "\033[2J\033[H";

    
    while(true){
        
        bool end=false;
        int c=0;
        int p_score;
        round_vars player;
        player.c=c;
        player.deck=deck;
        player.end=end;
        player.n=n;
        player.score=p_score;
        shuffle_deck(deck);
        cout <<"================== welcome ======================"<<endl;
        cout <<"=========== "<<"round "<<n<<" ============"<<endl;
        cout <<"======= Enter your bet (10k chips owned) ========"<<endl;
            //cin>>bet;
        while(end==false) {
            
            cout << "\033[2J\033[H";
            cout <<"=============== dealers hand ===================="<<endl;
            deck[c].draw_card("                      ",H);  
            c++;
            cout<<"\033[4A"<<"\r"<<"";
            deck[c].draw_card("       ");
            c++;
            cout<<endl;
            Sleep(1000);

            if(n=0){

            }

            if (bj(deck[c].t_n+deck[c+1].t_n)==1){
                cout<<"dealer got a black jack!!"<<endl;
                end=true;
            }
            
            if(end==false){
                cout <<"=============== players hand ===================="<<endl;
                deck[c].draw_card("                                                ");  
                cout<<"\033[4A"<<"\r"<<"";
                
                deck[c+3].draw_card("                                            ");
                p_score=deck[c+2].t_n+deck[c+3].t_n;
                cout<<endl<<"your score is: "<<p_score<<endl;
                c=c+3;
                if (deck[c+2].no=="A"||deck[c+3].no=="A"){

                }

                if (bj(p_score)==1){
                    cout<<"dealer got a black jack!!"<<endl;
                    end=true;
                }
                
                if(end==false){
                    
                    player_move(player);
                }
                
            }
        
        }
        n++;
        char ppp;
        cout<<"do you want to play again(y/n)"<<endl;
        cin >>ppp;
        

        
        if(ppp=='n'){
        return 0;
        }
    }
    return 0;


}

void sp_A(round_vars &player){
    if(player.deck[player.c])
}

void player_move(round_vars &player){
    char p_m;
    cout<<"Hit(H)/Stand(S)/Double down(D)"<<endl;
    cin >>p_m;
    cout<<"\033[8A]"<<"\r";
    if(p_m=='H'){
        hit(player);
    }
    else if(p_m=='S'){
       
    }
    else if(p_m=='D'){
        
    }

}

void hit(round_vars &player){
    for(int i=0;i<4;i++){
    player.spaces.pop_back();
    }
    
    player.c=player.c+1;
    player.deck[player.c].draw_card(player.spaces);  
    cout<<endl<<"your score is: "<<player.score<<endl;
    if(bust(player.deck[player.c].t_n,player.score)==1){
        cout<<"the player is bust !! "<<endl;
        player.end=true;
    }
    if(player.end==false){
        
        if(r_21(player.deck[player.c].t_n,player.score)==1){
            player.end=true;
        }
        if(player.end==false){
            player_move(player);
        }
    }

    


}

bool bust(int t_n_new,int old_score){
    if(t_n_new+old_score>21) {
        return 1;
    }
    return 0;
}
bool r_21(int t_n_new,int old_score){
    if(t_n_new+old_score==21) {
        return 1;
    }
    return 0;
}



bool bj(int score){
    if(score==21){
        return 1;
    }
    return 0;
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


