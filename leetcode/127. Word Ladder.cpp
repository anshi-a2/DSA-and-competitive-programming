// PROBLEM :


A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:

Every adjacent pair of words differs by a single letter.
Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
sk == endWord
Given two words, beginWord and endWord, and a dictionary wordList, return the number of words in the shortest transformation sequence from beginWord to endWord, or 0 if no such sequence exists.


Example 1:

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5
Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> cog", which is 5 words long.

Example 2:

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: 0
Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.


// SOLUTION :


class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // Use an unordered_set for fast lookup of words
        unordered_set<string> wordSet(wordList.begin(), wordList.end());

        // Early exit if the endWord is not in the dictionary
        if (wordSet.find(endWord) == wordSet.end()) return 0;

        // Queue for BFS: stores current word and transformation depth
        queue<pair<string, int>> q;
        q.push({beginWord, 1});  // Start with level 1

        while (!q.empty()) {
            auto [word, level] = q.front();
            q.pop();

            // If the word matches the target, return the transformation level
            if (word == endWord) return level;

            // Try changing every character of the word to 'a' - 'z'
            for (int i = 0; i < word.size(); ++i) {
                char originalChar = word[i];

                for (char ch = 'a'; ch <= 'z'; ++ch) {
                    if (ch == originalChar) continue; // Skip if same char

                    word[i] = ch; // Mutate character

                    // If the mutated word is in the dictionary
                    if (wordSet.count(word)) {
                        q.push({word, level + 1});  // Add to queue for next level
                        wordSet.erase(word);        // Mark word as visited
                    }
                }

                word[i] = originalChar; // Restore the character for next iteration
            }
        }

        // If no transformation sequence found
        return 0;
    }
};



