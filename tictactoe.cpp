//Tic Tac Toe Game in C++

#include<iostream>
using namespace std;
char space[3][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'}};
string n1,n2;
int row;
int column;
char turn='X';
int choice;
bool draw=false;
//Function to show the current status of the gaming board
void display_board()
{
    cout<<"    |          |   \n";
    cout<<" "<<space[0][0]<<"  |     "<<space[0][1]<<"    |  "<<space[0][2]<<"  \n";
    cout<<"    |          |   \n";
    cout<<"----|----------|------\n";
    cout<<"    |          |   \n";
    cout<<" "<<space[1][0]<<"  |     "<<space[1][1]<<"    |  "<<space[1][2]<<"  \n";
    cout<<"    |          |   \n";
    cout<<"----|----------|------\n";
    cout<<"    |          |   \n";
    cout<<" "<<space[2][0]<<"  |     "<<space[2][1]<<"    |  "<<space[2][2]<<"  \n";
    cout<<"    |          |   \n";
      
}
//Function to get the player input and update the board
void player_turn()
{
    if(turn=='X')
    {
        cout<<n1<<" Please enter your choice: ";
        cin>>choice;
    }
    if(turn=='O')
    {   
         cout<<n2<< " Please enter your choice: ";
        cin>>choice;

    }
    switch(choice){
        case 1: row=0; column=0; break;
        case 2: row=0; column=1; break;
        case 3: row=0; column=2; break;
        case 4: row=1; column=0; break;
        case 5: row=1; column=1; break;
        case 6: row=1; column=2; break;
        case 7: row=2; column=0; break;
        case 8: row=2; column=1; break;
        case 9: row=2; column=2; break;
        default: cout<<"Invalid Move";
            
    }

    if(turn == 'X' && space[row][column] != 'X' && space[row][column] != 'O')
    {
        
        space[row][column] = 'X';
        turn = 'O';
    }
    else if(turn == 'O' && space[row][column] != 'X' && space[row][column] != 'O'){
       
        space[row][column] = 'O';
        turn = 'X';
    }else {
        
        cout<<"Box already filled!\n Please choose another!!\n";
        player_turn();
    }
}
//Function to get the game status e.g. GAME WON, GAME DRAW GAME IN CONTINUE MODE
bool isGameover(){
    
    for(int i=0; i<3; i++)
    if(space[i][0] == space[i][1] && space[i][0] == space[i][2] || space[0][i] == space[1][i] && space[0][i] == space[2][i])
    return true;

   

    if(space[0][0] == space[1][1] && space[0][0] == space[2][2] || space[0][2] == space[1][1] && space[0][2] == space[2][0])
    return true;

    
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(space[i][j] != 'X' && space[i][j] != 'O')
            return false;
        }
    }

    draw = true;
    return false;
}
//Program Main Method
int main()
{
    cout<<"Enter the name of the first player:\n";
    getline(cin,n1);

    cout<<"Enter the name of the second player:\n";
    getline(cin,n2);
    cout<<n1<<" is player1 so he/she will play first\n";
    cout<<n2<<" is player2 so he/she will play second\n";
    while(!isGameover())
    {
       display_board();
        player_turn();
        isGameover(); 
    }
    if(turn == 'X' && draw == false){
        cout<<n2<<" Wins!!";
    }
    else if(turn == 'O' && draw == false){
        cout<<n1<<" Wins!!\n";
    }
    else
    cout<<"It's a draw";
}