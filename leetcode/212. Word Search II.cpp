// PROBLEM :


Given an m x n board of characters and a list of strings words, return all words on the board.

Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

Example 1:

Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
Output: ["eat","oath"]
  
Example 2:

Input: board = [["a","b"],["c","d"]], words = ["abcb"]
Output: []



// SOLUTION :



class Solution {
public:
    // Possible directions for moving: right, down, left, up
    vector<vector<int>> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}};
    
    // Final answer list to store found words
    vector<string> ans;
    
    // Board dimensions
    int m, n;

    // Trie node structure
    struct TrieNode {
        bool endOfWord;         // Marks end of a word
        string word;            // Stores the complete word (only at end node)
        TrieNode* children[26]; // Pointers to next characters (26 lowercase letters)
    };

    // Helper function to create a new Trie node
    TrieNode* getNode() {
        TrieNode* newNode = new TrieNode();
        newNode->endOfWord = false;
        newNode->word = "";
        for (int i = 0; i < 26; i++) {
            newNode->children[i] = NULL;
        }
        return newNode;
    }

    // Inserts a word into the Trie
    void insert(TrieNode* root, string word) {
        TrieNode* crawler = root;
        for (char &ch : word) {
            if (crawler->children[ch - 'a'] == NULL) {
                crawler->children[ch - 'a'] = getNode();
            }
            crawler = crawler->children[ch - 'a'];
        }
        crawler->endOfWord = true;
        crawler->word = word; // Save full word at terminal node
    }

    // DFS search in board guided by Trie
    void findWordsInTrie(vector<vector<char>>& board, TrieNode* root, int i, int j) {
        // Base case: out of bounds, visited, or character not in Trie
        if (i < 0 || i >= m || j < 0 || j >= n || 
            board[i][j] == '$' || root->children[board[i][j] - 'a'] == NULL) {
            return;
        }

        // Move to the next node in Trie
        root = root->children[board[i][j] - 'a'];

        // If this node is the end of a word, add it to result and mark as found
        if (root->endOfWord == true) {
            ans.push_back(root->word);
            root->endOfWord = false; // Avoid duplicate entries
        }

        // Mark the current cell as visited
        char temp = board[i][j];
        board[i][j] = '$';

        // Explore all 4 directions
        for (auto &dir : directions) {
            int i_ = i + dir[0];
            int j_ = j + dir[1];
            findWordsInTrie(board, root, i_, j_);
        }

        // Restore the original character (backtracking)
        board[i][j] = temp;
    }

    // Main function: builds Trie and starts DFS from every cell
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        m = board.size(), n = board[0].size();

        // Build Trie from word list
        TrieNode* root = getNode();
        for (string &word : words) {
            insert(root, word);
        }

        // Start DFS from each cell if the letter exists in Trie root
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                char ch = board[i][j];
                if (root->children[ch - 'a'] != NULL) {
                    findWordsInTrie(board, root, i, j);
                }
            }
        }

        return ans;
    }
};




 
