// PROBLEM :


The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.

Given an integer n, return the number of distinct solutions to the n-queens puzzle.


Example 1:

Input: n = 4
Output: 2
Explanation: There are two distinct solutions to the 4-queens puzzle as shown.
  
Example 2:

Input: n = 1
Output: 1


A queen can move:
Horizontally
Vertically
Diagonally

This means:
No two queens can be in the same row, column, or diagonal.


// SOLUTION :


class Solution {
public:
    // Helper function to check if it's safe to place a queen at board[row][col]
    bool isSafe(int row, int col, vector<string>& board) {
        int x = row, y = col;

        // Check left side of current row
        while (y >= 0) {
            if (board[x][y] == 'Q') return false;
            y--;
        }

        x = row;
        y = col;
        // Check upper-left diagonal
        while (x >= 0 && y >= 0) {
            if (board[x][y] == 'Q') return false;
            x--;
            y--;
        }

        x = row;
        y = col;
        // Check lower-left diagonal
        while (x < board.size() && y >= 0) {
            if (board[x][y] == 'Q') return false;
            x++;
            y--;
        }

        // Safe to place queen
        return true;
    }

    // Recursive function to try placing queens column by column
    int solve(int col, vector<string>& board) {
        // All queens are placed
        if (col == board.size()) return 1;

        int count = 0;

        // Try placing queen in every row of current column
        for (int row = 0; row < board.size(); row++) {
            if (isSafe(row, col, board)) {
                // Place queen
                board[row][col] = 'Q';

                // Recurse to place next queen in the next column
                count += solve(col + 1, board);

                // Backtrack and remove the queen
                board[row][col] = '.';
            }
        }

        return count;
    }

    // Main function to initialize board and start recursion
    int totalNQueens(int n) {
        vector<string> board(n);       // Board represented as vector of strings
        string s(n, '.');              // Empty row: "...."

        // Initialize board with empty rows
        for (int i = 0; i < n; i++) {
            board[i] = s;
        }

        // Start placing queens from column 0
        return solve(0, board);
    }
};



// SOLUTION 02 (Use 3 boolean arrays to track occupied rows and diagonals) :



class Solution {
public:
    // Main function to return the number of distinct solutions to the N-Queens problem
    int totalNQueens(int n) {
        // Boolean arrays to mark which rows and diagonals are under attack
        vector<bool> rows(n, false);              // Row attack status
        vector<bool> diag1(2 * n - 1, false);     // Top-left to bottom-right diagonals (row + col)
        vector<bool> diag2(2 * n - 1, false);     // Bottom-left to top-right diagonals (row - col + n - 1)
        
        // Start recursive backtracking from column 0
        return solve(0, n, rows, diag1, diag2);
    }

private:
    // Recursive helper function to try placing queens column by column
    int solve(int col, int n,
              vector<bool>& rows,
              vector<bool>& diag1,
              vector<bool>& diag2) {
        
        // If all columns are filled, we've found a valid solution
        if (col == n) return 1;

        int count = 0;  // Counts the number of valid arrangements

        // Try placing a queen in each row for the current column
        for (int row = 0; row < n; row++) {
            int d1 = row + col;         // Index for diag1 (↘ direction)
            int d2 = row - col + n - 1; // Index for diag2 (↙ direction)

            // Check if placing a queen at (row, col) is safe
            if (!rows[row] && !diag1[d1] && !diag2[d2]) {
                // Mark the row and diagonals as occupied
                rows[row] = diag1[d1] = diag2[d2] = true;

                // Move to the next column and continue placing queens
                count += solve(col + 1, n, rows, diag1, diag2);

                // Backtrack: remove the queen and unmark row and diagonals
                rows[row] = diag1[d1] = diag2[d2] = false;
            }
        }
        return count;  // Return the number of solutions found for this configuration
    }
};




