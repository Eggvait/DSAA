#include <iostream>
#include <vector>
using namespace std;

#define N 8  // You can change N to any board size

bool isSafe(vector<vector<int>>& board, int row, int col) {
    // Check column
    for (int i = 0; i < row; i++)
        if (board[i][col]) return false;

    // Check upper-left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j]) return false;

    // Check upper-right diagonal
    for (int i = row, j = col; i >= 0 && j < N; i--, j++)
        if (board[i][j]) return false;

    return true;
}

bool solveNQueens(vector<vector<int>>& board, int row) {
    if (row == N) return true;

    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1;
            if (solveNQueens(board, row + 1)) return true;
            board[row][col] = 0;  // backtrack
        }
    }

    return false;
}

void printBoard(vector<vector<int>>& board) {
    for (auto& row : board) {
        for (int val : row)
            cout << (val ? "Q " : ". ");
        cout << endl;
    }
}

int main() {
    vector<vector<int>> board(N, vector<int>(N, 0));

    if (!solveNQueens(board, 0))
        cout << "No solution exists\n";
    else {
        cout << "One of the possible N-Queens solutions:\n";
        printBoard(board);
    }

    return 0;
}
