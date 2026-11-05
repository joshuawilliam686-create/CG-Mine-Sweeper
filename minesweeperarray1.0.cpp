#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class MineSweeper{
private:
        static const int rows = 9;
        static const int cols = 15;
        int MINES;
        int MaxFlags;
        int TimeLimit;
        bool mines[rows][cols] = {};
        char board[rows][cols];
public:
 MineSweeper(){
    MINES = 20;
    MaxFlags = MINES - 2;
    TimeLimit = 300;

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            mines[i][j] = false;
        }
    }
}
void initializeBoard(){
         for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            board[i][j] = '-';
        }
    }
}

void placeMines(){
    int count = 0;

    while(count < MINES){
        int row = rand() % rows;
        int col = rand() % cols;

        if(mines[row][col] == false){
            mines[row][col] = true;
            count++;
        }
    }
}

int MinesPresent(int row, int col){
    int count = 0;

    for(int i = row - 1; i <= row + 1; i++){
        for(int j = col - 1; j <= col + 1; j++){
            if(i >= 0 && i < rows && j >= 0 && j < cols){
                if(mines[i][j] == true){
                    count++;
                }
            }
        }
    }

    return count;
}

void Board(){
    for(int i = 0; i < cols; i++){
        if(i < 10){
            cout << i << "  ";
        }
        else{
            cout << i << " ";
        }
    }
    cout << endl;
    for(int i = 0; i < rows; i++){
        cout << i << "  ";
        for(int j = 0; j < cols; j++){
            cout << board[i][j] << "  ";
        }
        cout << endl;
    }
}

void revealMines(){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(mines[i][j] == true){
                board[i][j] = '*';
            }
        }
    }
}

void play(){
   int moves = 0;
    int SafeCells = rows * cols - MINES;
    int flagsLeft = MaxFlags;
    bool gameOver = false;
    cout << " MINESWEEPER " << endl;
    cout << "Mines: " << MINES << endl;
    cout << "Flags: " << MaxFlags << endl;
    cout << "Time limit: " << TimeLimit << " seconds" << endl;
    cout << "Type o to open a cell or f to place/remove a flag" << endl;
    time_t startTime = time(0);

    while(gameOver == false){
        Board();
        int timeLeft = TimeLimit - (time(0) - startTime);
        cout << "Flags left: " << flagsLeft << endl;
        cout << "Time left: " << timeLeft << " seconds" << endl;
        char action;
        int row, col;

        cout << "Enter action (o = open, f = flag): ";
        cin >> action;
        cout << "Enter row: ";
        cin >> row;
        cout << "Enter column: ";
        cin >> col;

        if(time(0) - startTime >= TimeLimit){
            cout << " TIME IS UP!" << endl;
            revealMines();
            Board();
            cout << "GAME OVER!" << endl;
            gameOver = true;
            continue;
        }

        if(row < 0 || row >= rows || col < 0 || col >= cols){
            cout << "Invalid position! Try again." << endl;
            continue;
        }

        if(action == 'f' || action == 'F'){
            if(board[row][col] == 'F'){
                board[row][col] = '-';
                flagsLeft++;
                cout << "Flag removed." << endl;
            }
            else if(board[row][col] != '-'){
                cout << "You cannot put a flag on an opened cell!" << endl;
            }
            else if(flagsLeft == 0){
                cout << "No flags left!" << endl;
            }
            else{
                board[row][col] = 'F';
                flagsLeft--;
                cout << "Flag placed." << endl;
            }
            continue;
        }

        if(action != 'o' && action != 'O'){
            cout << "Invalid action! Use o or f." << endl;
            continue;
        }

        if(board[row][col] == 'F'){
            cout << "This cell has a flag! Remove it first." << endl;
            continue;
        }

        if(board[row][col] != '-'){
            cout << "This cell is already opened!" << endl;
            continue;
        }

        if(mines[row][col] == true){
            cout << "BOOM! You hit a mine!" << endl;
            revealMines();
            Board();
            cout << "GAME OVER!" << endl;
            gameOver = true;
        }

        else{
            int nearby = MinesPresent(row, col);
            board[row][col] = '0' + nearby;
            moves++;
            cout << "Safe move!" << endl;

            if(moves == SafeCells){
                Board();
                cout << "Congratulations! YOU WON!" << endl;
                gameOver = true;
            }
        }
    }
}
};

int main() {
    srand(time(0));
    MineSweeper Player;
    Player.initializeBoard();
    Player.placeMines();
    Player.play();
   
 return 0;
}