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
    // Main function to return all possible letter combinations for the given digit string
    vector<string> letterCombinations(string digits) {
        vector<string> res;  // To store the final list of combinations

        // Edge case: if input is empty, return empty result
        if (digits.empty()) return res;

        // Mapping of digits to their corresponding letters (like a phone keypad)
        unordered_map<char, string> digitToLetters = {
            {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"},
            {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}
        };

        // Start backtracking from index 0 with an empty string
        backtrack(digits, 0, "", res, digitToLetters);

        return res;
    }

private:
    // Helper function to build combinations using backtracking
    void backtrack(const string& digits, int idx, string comb,
                   vector<string>& res,
                   const unordered_map<char, string>& digitToLetters) {

        // Base case: if current index has reached the end of digits,
        // add the current combination to the result
        if (idx == digits.length()) {
            res.push_back(comb);
            return;
        }

        // Get the current digit and find its corresponding letters
        const string& letters = digitToLetters.at(digits[idx]);

        // For each letter corresponding to the current digit,
        // append it to the combination and continue recursion
        for (char letter : letters) {
            backtrack(digits, idx + 1, comb + letter, res, digitToLetters);
            // Note: comb + letter creates a new string each time (safe for recursion)
        }
    }
};


