// PROBLEM :


Given two strings s and t of lengths m and n respectively, return the minimum window substring of s such that every character in t (including duplicates) is included in the window. If there is no such substring, return the empty string "".

The testcases will be generated such that the answer is unique.

Example 1:

Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.
  
Example 2:

Input: s = "a", t = "a"
Output: "a"
Explanation: The entire string s is the minimum window.
  
Example 3:

Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.



// SOLUTION :


class Solution {
    #define SIZE 256+2
    bool equalFreq(vector<int>& curr,vector<int>& freq){//Check frequency of current window with freq(t)
        for(int i=0;i<SIZE;++i)
            if(freq[i]>0 and curr[i]<freq[i])
                return false;
        return true;
    }
public:
    string minWindow(string s, string t) {
        int n=s.size();
        if(n<t.size())
            return "";

        vector<int> freq(SIZE,0);
        for(char &c: t)//Find freq(t)
            freq[c]++;

        int l=0,r=0;//left and right pointers of sliding window
        int minWin = INT_MAX;
        string ans="";
        vector<int> curr(SIZE,0);
        
        while(r<n){ //run till end of string
            curr[s[r]]++;
            if(equalFreq(curr,freq)){//If we have all chars of t in our curr window
                do {    //move left ptr to as right as possible to minimize window size
                    curr[s[l]]--;
                    l++;
                }while(equalFreq(curr,freq));//Run until curr no more matches t
                if(minWin > r-l+2){//If curr window size is less than already know minWin size
                    minWin = r-l+2;
                    ans = s.substr(l-1,minWin);
                }
            }
            r++;
        }
        return ans;
    }
};
