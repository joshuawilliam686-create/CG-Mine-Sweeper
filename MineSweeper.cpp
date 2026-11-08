#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <queue>
using namespace std;


class MineSweeper{
private:
    static const int MAX_ROWS = 16;
    static const int MAX_COLS = 30;
    int rows;
    int cols;
    int MINES;
    int MaxFlags;
    int TimeLimit;
    bool mines[MAX_ROWS][MAX_COLS] = {};
    vector<vector<char>> board;

public:
    MineSweeper(int difficulty){
    if(difficulty == 1){
        rows = 5;
        cols = 5;
        MINES = 5;
        TimeLimit = 120;
    }
    else if(difficulty == 2){
        rows = 16;
        cols = 15;
        MINES = 20;
        TimeLimit = 180;
    }
    else{
        rows = 16;
        cols = 30;
        MINES = 99;
        TimeLimit = 210;
    }
    MaxFlags = MINES - 2;
    board.assign(rows, vector<char>(cols, '-'));
}

void internalBoard(){
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
                if (i >= 0 && i < rows &&
                    j >= 0 && j < cols) {
                    if (i == row && j == col) {
                        continue;
                    }
                    if (mines[i][j] == true) {
                        count++;
                    }
                }
            }
        }
        return count;
    }

   int revealEmptyCells(int row, int col){
       queue<pair<int, int>> cells;
       int revealed;
       int nearby = MinesPresent(row, col);
       board[row][col] = '0' + nearby;
       revealed++;
       if(nearby == 0){
           cells.push(make_pair(row, col));
       }

      while(!cells.empty()){
          pair<int, int> current = cells.front();
          cells.pop();
          int currentrow = current.first;
          int currentcol = current.second;
          for(int i = currentrow - 1; i <= currentrow + 1; i++){
              for(int j = currentcol - 1; j <= currentcol + 1; j++){
                  if(i >= 0 && i < rows && j >= 0 && j < cols){
                      if (board[i][j] == '-' && mines[i][j] == false){
                          int neighbourMines = MinesPresent(i, j);
                          board[i][j] = '0' + neighbourMines;
                          revealed++;
                          if(neighbourMines == 0){
                              cells.push(make_pair(i, j));
                          }
                      }
                  }
              }
          }
      }
          return revealed;
      }
   void RenderBoard(){
        for(int i = 0; i < cols; i++){
            if (i < 10) {
                cout << i << "  ";
            }
            else {
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
        cout << "MINESWEEPER " << endl;
        cout << "Mines: " << MINES << endl;
        cout << "Flags: " << MaxFlags << endl;
        cout << "Time limit: " << TimeLimit << " seconds" << endl;

        cout << "Type o to open a cell or f to place/remove a flag" << endl;
        time_t startTime = time(0);
        while (gameOver == false) {
            RenderBoard();
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
                cout << "TIME IS UP!" << endl;
                revealMines();
                RenderBoard();
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
                    cout << "You cannot put a flag on an opened cell!"
                         << endl;
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
                RenderBoard();
                cout << "GAME OVER!" << endl;
                gameOver = true;
            }
            else{
                int nearby = MinesPresent(row, col);
                if(nearby == 0){
                    int newrevealed = revealEmptycells(row, col);
                    moves = mpves + newrevealed;
                }
                else{
                    board[row][col] = '0' + nearby;
                    moves++;
                    cout << "Safe move!" << endl;
                }
                
                if(moves == SafeCells){
                    RenderBoard();
                    cout << "Congratulations! YOU WON!" << endl;
                    gameOver = true;
                }
            }
        }
    }
};

int main() {
    srand(time(0));
    int difficulty;
    cout <<"MineSweeper Game Play" << endl;
    cout << "Press 1 for easy Level" << endl;
    cout << "Press 2 for medium Level" << endl;
    cout << "Press 3 for hard Level" << endl;
    cout << "Select level: ";
    cin >> difficulty;
    if(difficulty < 1 || difficulty > 3){
        cout <<"Invalid Level, enter 1 for easy, 2 for medium, 3 for hard Levels!" << endl;
            }
    MineSweeper Player(difficulty);
    Player.internalBoard();
    Player.placeMines();
    Player.play();
    return 0;
}
