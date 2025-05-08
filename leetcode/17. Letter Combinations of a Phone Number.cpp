// PROBLEM :


Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.

A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.
 

Example 1:

Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
  
Example 2:

Input: digits = ""
Output: []
  
Example 3:

Input: digits = "2"
Output: ["a","b","c"]



// SOLUTION :


class Solution {
public:
    // Main function that generates all letter combinations for a given digit string
    vector<string> letterCombinations(string digits) {
        vector<string> res;

        // Edge case: if input is empty, return empty result
        if (digits.empty()) return res;

        // Mapping of digits to corresponding letters on a phone keypad
        const unordered_map<char, string> digitToLetters = {
            {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"},
            {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}
        };

        // Start backtracking from index 0 with an empty current combination
        string comb;
        comb.reserve(digits.size());  // Reserve space to avoid repeated reallocations
        backtrack(digits, 0, comb, res, digitToLetters);

        return res;        
    }

private:
    // Helper function to generate combinations using backtracking
    void backtrack(const string& digits, int idx, string& comb, 
                   vector<string>& res, const unordered_map<char, string>& digitToLetters) {
        // Base case: if combination is complete, add to results
        if (idx == digits.length()) {
            res.push_back(comb);
            return;
        }

        // Get possible letters for current digit
        const string& letters = digitToLetters.at(digits[idx]);

        // Explore each possible letter for this digit
        for (char letter : letters) {
            comb.push_back(letter);                          // Choose
            backtrack(digits, idx + 1, comb, res, digitToLetters); // Explore
            comb.pop_back();                                 // Un-choose (backtrack)
        }
    }    
};


