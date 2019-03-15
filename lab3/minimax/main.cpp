#include<iostream>
#include<algorithm>

using namespace std;

struct Move {
    int row, col;
};

char player = 'x', opponent = 'o';


bool isMovesLeft(char board[3][3]) { for (int i = 0; i<3; i++) for (int j = 0; j<3; j++) if (board[i][j]=='_') return true; return false; }

int evaluate(char b[3][3]) {
    for (int row = 0; row<3; row++)
        if (b[row][0]==b[row][1] && b[row][1]==b[row][2]) {
            if (b[row][0]=='x') return 1;
            else if (b[row][0]=='o') return -1;
        }

    for (int col = 0; col<3; col++)
        if (b[0][col]==b[1][col] && b[1][col]==b[2][col]) {
            if (b[0][col]=='x') return 1;
            else if (b[0][col]=='o') return -1;
        }

    if (b[0][0]==b[1][1] && b[1][1]==b[2][2]) {
        if (b[0][0]=='x') return 1;
        else if (b[0][0]=='o') return -1;
    }

    if (b[0][2]==b[1][1] && b[1][1]==b[2][0]) {
        if (b[0][2]=='x') return 1;
        else if (b[0][2]=='o') return -1;
    }

    return 0;
}

int minimax(char board[3][3], int depth, bool isMax) {
    int score = evaluate(board);
    if (score == 1) return score;
    if (score == -1) return score;
    if (isMovesLeft(board)==false) return 0;

    int best = isMax ? -1000 : 1000;
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            if (board[i][j]=='_')  {
                board[i][j] = isMax ? player : opponent;
                best =  isMax ? max( best, minimax(board, depth+1, !isMax)) : min(best, minimax(board, depth+1, !isMax));
                board[i][j] = '_';
            }
    return best;
}

Move findBestMove(char board[3][3])  {
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            if (board[i][j]=='_') {
                board[i][j] = player;
                int moveVal = minimax(board, 0, false);

                board[i][j] = '_';

                if (moveVal > bestVal) {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }

    return bestMove;
}

int main() {
    char board[3][3] = {
        { 'x', 'o', 'x' },
        { 'o', 'o', 'x' },
        { '_', '_', '_' }
    };

    int value = evaluate(board);
    cout << (value == 1 ? "Wygrales" : value == -1 ? "Przegrales" : "Remis") << endl;
    Move bestMove = findBestMove(board);
    cout << "Najlepszym ruchem będzie WIERSZ: " << bestMove.row << " KOLUMNA: " << bestMove.col << endl;
    return 0;
}
