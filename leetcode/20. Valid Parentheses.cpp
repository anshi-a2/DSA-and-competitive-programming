// PROBLEM :

Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Every close bracket has a corresponding open bracket of the same type.
 

Example 1:

Input: s = "()"

Output: true

Example 2:

Input: s = "()[]{}"

Output: true

Example 3:

Input: s = "(]"

Output: false

Example 4:

Input: s = "([])"

Output: true



// SOLUTION :


class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        int i=0;
        while(i<s.length()){
            if(s[i]=='(' || s[i]=='{' || s[i]=='['){
                st.push(s[i]);
            } else if(st.empty() ||
                (s[i]==')' && st.top()!='(') ||
                (s[i]==']' && st.top()!='[') ||
                (s[i]=='}' && st.top()!='{')
            ) {
                return false;
            } else {
                st.pop();
            }
            i++;
        }
        if(st.empty()) {
            return true;
        }
        return false;

        
    }
};


