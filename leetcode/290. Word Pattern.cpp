// PROBLEM :

iven a pattern and a string s, find if s follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in s. Specifically:

Each letter in pattern maps to exactly one unique word in s.
Each unique word in s maps to exactly one letter in pattern.
No two letters map to the same word, and no two words map to the same letter.
 

Example 1:

Input: pattern = "abba", s = "dog cat cat dog"

Output: true

Explanation:

The bijection can be established as:

'a' maps to "dog".
'b' maps to "cat".
  
Example 2:

Input: pattern = "abba", s = "dog cat cat fish"

Output: false

Example 3:

Input: pattern = "aaaa", s = "dog cat cat dog"

Output: false


// SOLUTION :

class Solution {
public:
    bool wordPattern(string pattern, string s) {
        vector<string>b;
        int i=0;
        while (i<s.size()){
            while (i<s.size() && s[i]==' '){i++;}
            string k="";
            while (i<s.size() && s[i]!=' '){k+=s[i];i++;}
            b.push_back(k);
        }
        if (pattern.size()!=b.size()){return false;}
        unordered_map <char,string> mp;
        for (int i=0;i<pattern.size();i++){
            mp[pattern[i]]=b[i];
        }
        string ans="";
        for (int i=0;i<pattern.size();i++){
            for (auto &it:mp){
                if (pattern[i]==it.first){
                    ans+=it.second;
                }
            }
            ans+=' ';
        }
        ans.pop_back();
        unordered_map<string,char> ma;
        for (int i=0;i<b.size();i++){
            ma[b[i]]=pattern[i];
        }
        string bns="";
        for (int i=0;i<b.size();i++){
            for (auto &it:ma){
                if (b[i]==it.first){
                    bns+=it.second;
                }
            }
        }
        return (ans==s)&&(bns==pattern);
    }
};


// SOLUTION 02 : ( MORE OPTIMIZED )


class Solution {
public:
    bool wordPattern(string pattern, string s) {
        istringstream iss(s);
        vector<string> words;
        string word;

        while (iss >> word) {
            words.push_back(word);
        }

        if (pattern.size() != words.size()) {
            return false;
        }

        unordered_map<char, string> charToWord;
        unordered_map<string, char> wordToChar;

        for (int i = 0; i < pattern.size(); ++i) {
            char c = pattern[i];
            const string& w = words[i];

            if ((charToWord.count(c) && charToWord[c] != w) ||
                (wordToChar.count(w) && wordToChar[w] != c)) {
                return false;
            }

            charToWord[c] = w;
            wordToChar[w] = c;
        }

        return true;
    }
};



