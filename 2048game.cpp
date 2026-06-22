#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<cctype>
using namespace std;

class Board{
    private:
    int grid[4][4];

    public:
    Board(){
        srand(time(0));
        initialize_Board();
    }

    void initialize_Board(){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                grid[i][j]=0;
            }
        }
        int count=0;
        while(count<2)
        {
            int i=rand()%4;
            int j=rand()%4;
            if(grid[i][j]==0)
            {
                grid[i][j]=(rand()%10==0)?4:2;
                count++;
            }
        }
    }

    void add_randtile(){
        int emptycount=0;
        int emptycell[16][2];
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(grid[i][j]==0){
                    emptycell[emptycount][0]=i;
                    emptycell[emptycount][1]=j;
                    emptycount++;
                }
            }
        }
        if(emptycount>0){
            int r=rand()%emptycount;
            int i=emptycell[r][0];
            int j=emptycell[r][1];
            grid[i][j]=(rand()%10==0)?4:2;
        }
    }

    void display_Board(){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                cout<<grid[i][j]<<"\t";
            }
            cout<<endl;
        }
    }

    int merge_tiles(char direction){
        int merged=0;
        direction=toupper(direction);
        switch(direction){
            case 'W':
             for(int j=0;j<4;j++){
                for(int i=0;i<3;i++){
                    for(int k=i+1;k<4;k++){
                        if(grid[k][j]!=0){
                            if(grid[i][j]==0){
                                grid[i][j]=grid[k][j];
                                grid[k][j]=0;
                                i--;
                                break;
                            }
                            else if(grid[i][j]==grid[k][j]){
                                grid[i][j]*=2;
                                merged += grid[i][j];
                                grid[k][j]=0;
                                break;
                            }
                            else break;
                        }
                    }
                }
            }
            add_randtile();
            break;
            case 'S':
            for(int j=0;j<4;j++){
                for(int i=3;i>0;i--){
                    for(int k=i-1;k>=0;k--){
                        if(grid[k][j]!=0){
                            if(grid[i][j]==0){
                                grid[i][j]=grid[k][j];
                                grid[k][j]=0;
                                i++;
                                break;
                            }
                            else if(grid[i][j]==grid[k][j]){
                                grid[i][j]*=2;
                                merged += grid[i][j]; 
                                grid[k][j]=0;
                                break;
                            }
                            else break;
                        }
                    }
                }
            }
            add_randtile();
            break;
            case 'A':
            for(int i=0;i<4;i++){
                for(int j=0;j<3;j++){
                    for(int k=j+1;k<4;k++){
                        if(grid[i][k]!=0){
                            if(grid[i][j]==0){
                                grid[i][j]=grid[i][k];
                                grid[i][k]=0;
                                j--;
                                break;
                            }
                            else if(grid[i][j]==grid[i][k]){
                                grid[i][j]*=2;
                                merged += grid[i][j]; 
                                grid[i][k]=0;
                                break;
                            }
                            else break;
                        }
                    }
                }
            }
            add_randtile();
            break;
            case 'D':
            for(int i=0;i<4;i++){
                for(int j=3;j>0;j--){
                    for(int k=j-1;k>=0;k--){
                        if(grid[i][k]!=0){
                            if(grid[i][j]==0){
                                grid[i][j]=grid[i][k];
                                grid[i][k]=0;
                                j++;
                                break;
                            }
                            else if(grid[i][j]==grid[i][k]){
                                grid[i][j]*=2;
                                merged += grid[i][j]; 
                                grid[i][k]=0;
                                break;
                            }
                            else break;
                        }
                    }
                }
            }
            add_randtile();
            break;
            default:{
                cout<<"invalid choice."<<endl;
            }
        }
        return merged;
    }

    bool isgame_over(){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(grid[i][j]==2048){
                    cout<<"Congratulations! You have successfully completed the game."<<endl;
                    return true;
                }
            }
        }
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(grid[i][j]==0){
                    return false;
                }
            }
        }
        for(int i=0;i<4;i++){
            for(int j=0;j<3;j++){
                if(grid[i][j]==grid[i][j+1]){
                    return false;
                }
            }
        }
        for(int j=0;j<4;j++){
            for(int i=0;i<3;i++){
                if(grid[i][j]==grid[i+1][j]){
                    return false;
                }
            }
        }
        cout<<"Game Over! No more moves possible."<<endl;
        return true;
    }
};
class Game{
    private:
    Board board;
    int score;
    int choice;

    public:
    Game(){
        score=0;
        choice=0;
        cout<<"Welcome to the 2048 Game!"<<endl;
    }
    void Menu(){
        int n;
        cout<<"1) play game."<<endl;
        cout<<"2) show solution."<<endl;
        cout<<"Enter your choice: "<<endl;
        cin>>n;
        if(n==1)
        {
            playgame();
        }
        else{
            show_solution();
        }
    }
    void confirm_quit(){
        char confirm;
        cout<<"Are you sure you want to quit? (Y/N): "<<endl;
        cin>>confirm;
        if(toupper(confirm)=='Y'){
            cout<<"You quit the game."<<endl;
            exit(0);
        }
    }
    void process_move(char move){
        if(move=='W' || move=='S' || move=='A'|| move=='D'){
            int merged=board.merge_tiles(move);
            score+=merged;
            choice++;
            cout<<"Current Score: "<<score<<endl;
            if(board.isgame_over()){
                board.display_Board();
                cout << "Your Final Score: " << score << endl;
                exit(0);
            }
        }
        else if(move=='Q'){
            confirm_quit();
        }
        else{
            cout<<"Invalid choice!!"<<endl;
        }
    }
    void playgame(){
        char move;
        cout<<"press W to UP."<<endl;
        cout<<"press S to DOWN."<<endl;
        cout<<"press A to LEFT."<<endl;
        cout<<"press D to RIGHT."<<endl;
        cout<<"press Q to QUIT."<<endl;
        while(true){
            board.display_Board();
            cout<<"Enter your move: ";
            cin>>move;
            move=toupper(move);
            process_move(move);
        }
    }
    void show_solution(){
        Board demo;
        demo.display_Board();
        string moves="AASSWWDD";
        for(int i=0;i<moves.length();i++){
            cout<<"move: "<<moves[i]<<endl;
            demo.merge_tiles(moves[i]);
            demo.display_Board();
        }
    }
};
int main(){
    Game game;
    game.Menu();
    cout<<"Thank you for playing 2048! Goodbye!"<<endl;
    return 0;
}