// PROBLEM :


Given a string s representing a valid expression, implement a basic calculator to evaluate it, and return the result of the evaluation.
Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().


Example 1:

Input: s = "1 + 1"
Output: 2
  
Example 2:

Input: s = " 2-1 + 2 "
Output: 3
  
Example 3:

Input: s = "(1+(4+5+2)-3)+(6+8)"
Output: 23



// SOLUTION :


class Solution {
public:
    int calculate(string s) {
        stack<int>st;
        int operand = 0, sign = 1, result = 0;

        for(char ch: s){
            if(isdigit(ch)){
                operand = operand*10 + (ch-'0');
            }else if(ch == '+'){
                result+=sign*operand;
                sign=1;
                operand=0;
            }else if(ch == '-'){
                result+=sign*operand;
                sign=-1;
                operand=0;
            }else if(ch == '('){
                st.push(result);
                st.push(sign);
                result=0;
                sign=1;
            }else if(ch == ')'){
                result+=sign*operand;
                operand=0;
                result*=st.top();st.pop(); //for the sign 
                result+=st.top();st.pop(); //for the value
            }
        }
        return result + (sign*operand);
    }
};



 
