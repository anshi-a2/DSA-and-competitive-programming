A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters include letters and numbers.

Given a string s, return true if it is a palindrome, or false otherwise.


Example 1:

Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.
  
Example 2:

Input: s = "race a car"
Output: false
Explanation: "raceacar" is not a palindrome.


// SOLUTION :

class Solution {
public:
    bool isPalindrome(string s) {
        int l=0;
        int r=s.size()-1;
        transform(s.begin(), s.end(), s.begin(), ::tolower);;
        while(l<r){
            if((isdigit(s[l]) or isalpha(s[l])) && (isdigit(s[r]) or isalpha(s[r]))){
                if(s[l]!=s[r]){
                    return false;
                } else{
                    l++;
                    r--;
                }
            } else if(!(isdigit(s[l]) or isalpha(s[l]))){
                l++;
            } else{
                r--;
            }
        }
        return true;
    }
};



// SOLUTION 02 (few optimizations) :

class Solution {
public:
    bool isPalindrome(string s) {
        int l = 0, r = s.size() - 1;
        
        while (l < r) {
            // Skip non-alphanumeric characters
            if (!isalnum(s[l])) {
                l++;
            } else if (!isalnum(s[r])) {
                r--;
            } else {
                // Compare characters after converting to lowercase
                if (tolower(s[l]) != tolower(s[r])) {
                    return false;
                }
                l++;
                r--;
            }
        }
        
        return true;
    }
};
