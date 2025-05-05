// PROBLEM :


According to Wikipedia's article: "The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970."

The board is made up of an m x n grid of cells, where each cell has an initial state: live (represented by a 1) or dead (represented by a 0). Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules (taken from the above Wikipedia article):

Any live cell with fewer than two live neighbors dies as if caused by under-population.
Any live cell with two or three live neighbors lives on to the next generation.
Any live cell with more than three live neighbors dies, as if by over-population.
Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
The next state of the board is determined by applying the above rules simultaneously to every cell in the current state of the m x n grid board. In this process, births and deaths occur simultaneously.

Given the current state of the board, update the board to reflect its next state.

Note that you do not need to return anything.

Example 1:

Input: board = [[0,1,0],[0,0,1],[1,1,1],[0,0,0]]
Output: [[0,0,0],[1,0,1],[0,1,1],[0,1,0]]
  
Example 2:

Input: board = [[1,1],[1,0]]
Output: [[1,1],[1,1]]



// SOLUTION :


class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int m = board.size();
        int n = board[0].size();

        // First pass: Apply rules and mark transitions using encoded states
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                int live = 0;

                // Count live neighbors (including those marked as 2, which means they were originally alive)
                if(i-1 >= 0 && (board[i-1][j] == 1 || board[i-1][j] == 2)) live++; 
                if(i+1 < m && (board[i+1][j] == 1 || board[i+1][j] == 2)) live++; 
                if(j-1 >= 0 && (board[i][j-1] == 1 || board[i][j-1] == 2)) live++; 
                if(j+1 < n && (board[i][j+1] == 1 || board[i][j+1] == 2)) live++; 
                if(i-1 >= 0 && j-1 >= 0 && (board[i-1][j-1] == 1 || board[i-1][j-1] == 2)) live++; 
                if(i-1 >= 0 && j+1 < n && (board[i-1][j+1] == 1 || board[i-1][j+1] == 2)) live++; 
                if(i+1 < m && j-1 >= 0 && (board[i+1][j-1] == 1 || board[i+1][j-1] == 2)) live++; 
                if(i+1 < m && j+1 < n && (board[i+1][j+1] == 1 || board[i+1][j+1] == 2)) live++; 

                // Apply the Game of Life rules:
                // Rule 1 or 3: live cell with <2 or >3 live neighbors dies → mark as 2 (live -> dead)
                if(board[i][j] == 1){
                    if(live < 2 || live > 3)
                        board[i][j] = 2;
                }
                // Rule 4: dead cell with exactly 3 live neighbors becomes alive → mark as 3 (dead -> live)
                else {
                    if(live == 3)
                        board[i][j] = 3;
                }
            }
        }

        // Second pass: finalize the board by converting intermediate states
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                // Cell was live and is now dead
                if(board[i][j] == 2) board[i][j] = 0;
                // Cell was dead and is now live
                if(board[i][j] == 3) board[i][j] = 1;
            }
        }
    }
};


// SOLUTION 02 (more cleaner) :


class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int m = board.size(), n = board[0].size();

        // Direction vectors for 8 neighbors
        const vector<pair<int, int>> directions = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1},
            {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
        };

        // First pass: Apply rules with temporary markers
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int live = 0;

                // Count live neighbors
                for (auto [dx, dy] : directions) {
                    int ni = i + dx, nj = j + dy;
                    if (ni >= 0 && ni < m && nj >= 0 && nj < n &&
                        (board[ni][nj] == 1 || board[ni][nj] == 2)) {
                        ++live;
                    }
                }

                // Apply rules and mark changes
                if (board[i][j] == 1 && (live < 2 || live > 3)) {
                    board[i][j] = 2; // 1 -> 0
                } else if (board[i][j] == 0 && live == 3) {
                    board[i][j] = 3; // 0 -> 1
                }
            }
        }

        // Second pass: Finalize the updates
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 2) board[i][j] = 0;
                else if (board[i][j] == 3) board[i][j] = 1;
            }
        }
    }
};







