#include<bits/stdc++.h>
using namespace std;


// input
// Number of snakes (s) followed by s lines each containing 2 numbers denoting the head and tail positions of the snake.
// Number of ladders (l) followed by l lines each containing 2 numbers denoting the start and end positions of the ladder.
// Number of players (p) followed by p lines each containing a name.
// After taking these inputs, you should print all the moves in the form of the current player name followed by a random number between 1 to 6 denoting the die roll and the initial and final position based on the move.
// Format: <player_name> rolled a <dice_value> and moved from <initial_position> to <final_position>
class Dice{
    public:
    int diceThrow(){
        int random = rand();
        return (random%6) + 1;
    }
};



class Player{
    public:
    string name;
    int current_position;
    Player(string name){
        this->name = name;
        this->current_position = 1;
    }
};


class Node{
    public:
    int key; // the number at game node.
    Node *ladder;
    Node *snakeBite;
    Node *next;

    bool hasSnake;
    bool hasLadder;
    // ladder 
    // snakes
    Node(long long key){
        this->key = key;
        this->next = nullptr;
    }
};

class GameBoard{
    public:
    vector<Node*> board;
    GameBoard(){
        board.resize(101);
        
        for(int i = 100; i>=0; i--){
            Node *temp = new Node(i);
            board[i] = temp;
            if(i < 100){
                board[i]->next = board[i+1];
            }
            
        }
    }

    void addSnakes(vector<pair<long,long>> snakeList){
        for(auto x: snakeList){
            board[x.first]->hasSnake = true;
            board[x.first]->snakeBite = board[x.second];
        }
    }

    void addLadder(vector<pair<long,long>> ladderList){
        for(auto x: ladderList){
            board[x.first]->hasLadder = true;
            board[x.first]->ladder = board[x.second];
        }
    }
    
};





class SnakeAndLadderGame{
    public:
    /*
    Let's define some of the functionality for the game 
            -> input() : takes in the layout of the board. position of ladders snakes and players
            -> gameBegin(): starts the game this will take the following things as input gameBoard, playerllist
            -> initialisation(): initializes the board with snakes and ladders

    */
   int winnerCount = 0;
   vector<Player> playerList;
   GameBoard gboard;
   vector<string> playerListIP;
   vector<pair<long,long>> ladderList;
   vector<pair<long,long>> snakeList;

   void initialise(){
       // initialise game board
        gboard = GameBoard();
        gboard.addLadder(ladderList);
        gboard.addSnakes(snakeList);
       // initialise players
       for(auto x: playerListIP){
           this->playerList.push_back(Player(x));
       }
   }


   void describeGameBoard(){
       for(int i = 1; i<100; i++){
            Node *temp = gboard.board[i];
            cout << "key: " << temp->key <<" next-> " << temp->next->key << " " << temp->hasLadder << " " << temp-> hasSnake;
            if(temp->hasSnake){
                cout << "snake bite "<< temp->snakeBite->key << " ";
            } 
            if(temp->hasLadder){
                cout << "ladder " << temp->ladder->key; 
            }
            cout << endl;
       }
   }
   
   void gameBegin(){
       Dice dice = Dice();
       while(this->winnerCount < this->playerList.size()-1){
           for(int i = 0; i<playerList.size(); i++){
               int cnt = dice.diceThrow();
               int curr_pos = playerList[i].current_position;
               int new_pos = (curr_pos + cnt <= 100)?curr_pos + cnt: curr_pos;
               while (gboard.board[new_pos]->hasLadder || gboard.board[new_pos]->hasSnake )
               {
                    if(gboard.board[new_pos]->hasLadder){
                        // climb
                        new_pos = playerList[i].current_position = gboard.board[new_pos]->ladder->key;
                    }
                    else if(gboard.board[new_pos]->hasSnake){
                        // bite
                        new_pos = playerList[i].current_position = gboard.board[new_pos]->snakeBite->key;
                    }
                   
               }
               cout << playerList[i].name << " rolled a " << cnt <<" and moved from " <<curr_pos << " to " <<new_pos << endl;
               if(new_pos == 100){
                this->winnerCount++;
                cout << playerList[i].name << "has won !! \n";
               }
           }
       }
   }


   void input(){
       long long no_of_snakes;
       cout << "\n Enter the number of snakes";
       cin >> no_of_snakes;
       vector<pair<long,long>> snakesList;
       for(int i = 0; i<no_of_snakes; i++){
           long long start;
           long long end;
           cin >> start >> end;
           snakesList.push_back({start,end});
        } 
        this->snakeList = snakesList;
       cout << "\n Enter the ladders";
       long long no_ladders;
       vector<pair<long,long>> ladderList;
       cin >> no_ladders;
       for(int i = 0; i<no_ladders; i++){
           long long start;
           long long end;
           cin >> start >> end;
           ladderList.push_back({start,end});
       }
       this->ladderList = ladderList;
       cout << "\n Enter the players";
       long long no_of_players;
       cin >> no_of_players;
       vector<string> playerList;
       for(int i = 0; i<no_of_players; i++){
           string name;
           cin >> name;
           playerListIP.push_back(name);
       }

   }
};


int main(){
    SnakeAndLadderGame snl;
    snl.input();
    snl.initialise();
    snl.describeGameBoard();
    snl.gameBegin();

}
