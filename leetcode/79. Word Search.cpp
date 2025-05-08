// PROBLEM :

Given an m x n grid of characters board and a string word, return true if word exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.

Example 1:

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
Output: true
  
Example 2:

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
Output: true
  
Example 3:

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
Output: false


// SOLUTION :


class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int rows = board.size();
        int cols = board[0].size();
        
        // To track visited cells during DFS, we use a set of "row,col" strings
        unordered_set<string> visited;

        // Define a recursive lambda for DFS
        auto dfs = [&](int r, int c, int k, auto& dfs) -> bool {
            // Base case: all characters have been matched
            if (k == word.length()) return true;

            // Boundary check and conditions to return false:
            // - out of bounds
            // - cell already visited
            // - current board character doesn't match the current word character
            string key = to_string(r) + "," + to_string(c);
            if (r < 0 || r >= rows || c < 0 || c >= cols || visited.count(key) || board[r][c] != word[k]) {
                return false;
            }

            // Mark the current cell as visited
            visited.insert(key);

            // Explore 4 directions: up, down, left, right
            bool res = dfs(r + 1, c, k + 1, dfs) ||
                       dfs(r - 1, c, k + 1, dfs) ||
                       dfs(r, c + 1, k + 1, dfs) ||
                       dfs(r, c - 1, k + 1, dfs);

            // Backtrack: unmark the cell
            visited.erase(key);

            return res;
        };

        // Optimization: if the word is more likely to start from the end, reverse it
        unordered_map<char, int> count;
        for (char c : word) count[c]++;
        if (count[word[0]] > count[word.back()]) {
            reverse(word.begin(), word.end());
        }

        // Try starting DFS from every cell in the board
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (dfs(r, c, 0, dfs)) {
                    return true; // Found a valid path
                }
            }
        }

        return false; // No valid path found
    }
};



// SOLUTION 02 (in place check instead of visited list) :


class Solution {
public:
    // Directions: down, up, right, left
    const vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    
    bool exist(vector<vector<char>>& board, string word) {
        int rows = board.size();
        int cols = board[0].size();

        // Optional optimization: reverse word if ending character is rarer
        unordered_map<char, int> count;
        for (auto& row : board)
            for (char c : row)
                count[c]++;
        
        if (count[word[0]] > count[word.back()])
            reverse(word.begin(), word.end());

        // DFS function to search for word
        function<bool(int, int, int)> dfs = [&](int r, int c, int index) -> bool {
            // Base case: all characters matched
            if (index == word.size()) return true;

            // Boundary or mismatch check
            if (r < 0 || r >= rows || c < 0 || c >= cols || board[r][c] != word[index])
                return false;

            char temp = board[r][c];  // Save current character
            board[r][c] = '#';        // Mark cell as visited

            for (auto& [dr, dc] : directions) {
                if (dfs(r + dr, c + dc, index + 1)) {
                    board[r][c] = temp;  // Restore before returning
                    return true;
                }
            }

            board[r][c] = temp;  // Restore character (backtracking)
            return false;
        };

        // Try DFS from every cell
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (dfs(r, c, 0)) {
                    return true;
                }
            }
        }

        return false;
    }
};




 
