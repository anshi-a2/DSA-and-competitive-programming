// PROBLEM :

Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string "".

Example 1:

Input: strs = ["flower","flow","flight"]
Output: "fl"
  
Example 2:

Input: strs = ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.


// SOLUTION :

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) return "";

        string pref = strs[0];
        int prefLen = pref.length();

        for (int i = 1; i < strs.size(); i++) {
            string s = strs[i];
            while (prefLen > s.length() || pref != s.substr(0, prefLen)) {
                prefLen--;
                if (prefLen == 0) {
                    return "";
                }
                pref = pref.substr(0, prefLen);
            }
        }

        return pref;  
    }
};



or 


class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) return "";

        string& pref = strs[0];
        int prefLen = pref.length();

        for (int i = 1; i < strs.size(); ++i) {
            int j = 0;
            while (j < prefLen && j < strs[i].length() && pref[j] == strs[i][j]) {
                ++j;
            }
            prefLen = j;
            if (prefLen == 0) return "";
        }

        return pref.substr(0, prefLen);
    }
};
