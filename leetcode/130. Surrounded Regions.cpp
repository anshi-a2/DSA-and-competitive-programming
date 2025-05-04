// PROBLEM :

You are given an m x n matrix board containing letters 'X' and 'O', capture regions that are surrounded:

Connect: A cell is connected to adjacent cells horizontally or vertically.
Region: To form a region connect every 'O' cell.
Surround: The region is surrounded with 'X' cells if you can connect the region with 'X' cells and none of the region cells are on the edge of the board.
To capture a surrounded region, replace all 'O's with 'X's in-place within the original board. You do not need to return anything.

 
Example 1:

Input: board = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]

Output: [["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]

Explanation:


In the above diagram, the bottom region is not captured because it is on the edge of the board and cannot be surrounded.

Example 2:

Input: board = [["X"]]

Output: [["X"]]



// SOLUTION :


class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int rows = board.size();
        if (rows == 0) return;
        int cols = board[0].size();

        queue<pair<int, int>> q;

        // Step 1: Traverse borders, and enqueue all 'O's
        for (int r = 0; r < rows; ++r) {
            if (board[r][0] == 'O') q.emplace(r, 0);
            if (board[r][cols - 1] == 'O') q.emplace(r, cols - 1);
        }
        for (int c = 0; c < cols; ++c) {
            if (board[0][c] == 'O') q.emplace(0, c);
            if (board[rows - 1][c] == 'O') q.emplace(rows - 1, c);
        }

        // Step 2: BFS to mark all connected 'O's from borders as 'E' (escaped)
        const int dir[5] = {0, 1, 0, -1, 0};
        while (!q.empty()) {
            auto [r, c] = q.front(); q.pop();

            if (board[r][c] != 'O') continue;
            board[r][c] = 'E';  // Mark as escaped

            for (int i = 0; i < 4; ++i) {
                int nr = r + dir[i], nc = c + dir[i + 1];
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && board[nr][nc] == 'O') {
                    q.emplace(nr, nc);
                }
            }
        }

        // Step 3: Final pass to flip surrounded 'O's to 'X' and restore 'E' to 'O'
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (board[r][c] == 'O') {
                    board[r][c] = 'X';  // Surrounded region
                } else if (board[r][c] == 'E') {
                    board[r][c] = 'O';  // Border-connected region
                }
            }
        }
    }
};



// SOOLUTION 02: (refactored code with bfs in different method) :


class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int rows = board.size();
        if (rows == 0) return;
        int cols = board[0].size();

        // Enqueue border 'O's (avoid duplicates at corners)
        for (int r = 0; r < rows; ++r) {
            if (board[r][0] == 'O') bfs(board, r, 0, rows, cols);
            if (board[r][cols - 1] == 'O') bfs(board, r, cols - 1, rows, cols);
        }
        for (int c = 1; c < cols - 1; ++c) {
            if (board[0][c] == 'O') bfs(board, 0, c, rows, cols);
            if (board[rows - 1][c] == 'O') bfs(board, rows - 1, c, rows, cols);
        }

        // Final pass: flip 'O' → 'X', and 'E' → 'O'
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (board[r][c] == 'O') board[r][c] = 'X';
                else if (board[r][c] == 'E') board[r][c] = 'O';
            }
        }
    }

private:
    void bfs(vector<vector<char>>& board, int startRow, int startCol, int rows, int cols) {
        queue<pair<int, int>> q;
        q.emplace(startRow, startCol);

        const vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        while (!q.empty()) {
            auto [r, c] = q.front(); q.pop();
            if (board[r][c] != 'O') continue;

            board[r][c] = 'E'; // Mark as escaped

            for (const auto& [dr, dc] : directions) {
                int nr = r + dr, nc = c + dc;
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && board[nr][nc] == 'O') {
                    q.emplace(nr, nc);
                }
            }
        }
    }
};
