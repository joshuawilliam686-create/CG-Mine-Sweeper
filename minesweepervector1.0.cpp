#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class MineSweeper{
private:
    static  const int rows = 9;
    static const int columns = 15;
    int Mines;
    int MaxFlags;
    int TimeLimit;
    vector<vector<bool>> mines;
    vector<vector<char>> board;
public:
 MineSweeper(){
    Mines = 20;
    MaxFlags = Mines - 2;
    TimeLimit = 300;

    mines = vector<vector<bool>>(rows, vector<bool>(columns, false));
    board = vector<vector<char>>(rows, vector<char>(columns, '-'));
}

void internalboard(){
    for(auto &row : board){
        for(auto &cell : row) {
            cell = '-';
        }
    }
}

void placeMines(){
    int count = 0;

    while(count < Mines){
        int row = rand() % rows;
        int col = rand() % columns;

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
            if(i >= 0 && i < rows && j >= 0 && j < columns){
                if(mines[i][j] == true){
                    count++;
                }
            }
        }
    }
    return count;
}


void renderBoard(){
    vector<int> columnNumbers(columns);
    int num = 0;

    for(auto &col : columnNumbers){
        col = num;
        num++;
    }

    for(auto col : columnNumbers){
        if(col < 10){
            cout << col << "  ";
        }
        else {
            cout << col << " ";
        }
    }
    cout << endl;
    int rowNumber = 0;

    for(auto &row : board){
        cout << rowNumber << "  ";

        for(auto cell : row){
            cout << cell << "  ";
        }
        cout << endl;
        rowNumber++;
    }
}

void revealMines(){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            if (mines[i][j] == true) {
                board[i][j] = '*';
            }
        }
    }
}

void play(){
   int moves = 0;
    int SafeCells = rows * columns - Mines;
    int flagsLeft = MaxFlags;
    bool gameOver = false;
    cout << " MINESWEEPER " << endl;
    cout << "Mines: " << Mines << endl;
    cout << "Flags: " << MaxFlags << endl;
    cout << "Time limit: " << TimeLimit << " seconds" << endl;
    cout << "Type o to open a cell or f to place/remove a flag" << endl;
    time_t startTime = time(0);

    while(gameOver == false){
        renderBoard();
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
            renderBoard();
            cout << "GAME OVER!" << endl;
            gameOver = true;
            continue;
        }

        if(row < 0 || row >= rows || col < 0 || col >= columns){
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
            renderBoard();
            cout << "GAME OVER!" << endl;
            gameOver = true;
        }

        else{
            int nearby = MinesPresent(row, col);
            board[row][col] = '0' + nearby;
            moves++;
            cout << "Safe move!" << endl;

            if(moves == SafeCells){
                renderBoard();
                cout << "Congratulations! YOU WON!" << endl;
                gameOver = true;
            }
        }
    }
}

void startGame(){
    internalboard();
    placeMines();
    play();
}
};

int main(){
    srand(time(0));
    MineSweeper Player;
    Player.startGame();
 return 0;
}
