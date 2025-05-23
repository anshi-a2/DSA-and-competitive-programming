// PROBLEM :


You are given an array prices where prices[i] is the price of a given stock on the ith day.

Find the maximum profit you can achieve. You may complete at most two transactions.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

Example 1:

Input: prices = [3,3,5,0,0,3,1,4]
Output: 6
Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.
  
Example 2:

Input: prices = [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are engaging multiple transactions at the same time. You must sell before buying again.
  
Example 3:

Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.



// SOLUTION (state machine-based dynamic programming) :


int maxProfit(vector<int>& prices) {
    // If no prices are given, profit is zero
    if (prices.empty()) return 0;

    // Initialize four states:
    // s1: Max profit after 1st buy (negative because you spend money)
    // s2: Max profit after 1st sell
    // s3: Max profit after 2nd buy (subtracting again)
    // s4: Max profit after 2nd sell (final result)
    int s1 = -prices[0];
    int s2 = INT_MIN;
    int s3 = INT_MIN;
    int s4 = INT_MIN;

    for (int i = 1; i < prices.size(); ++i) {
        // Update each state based on the previous states and current price
        s1 = max(s1, -prices[i]);           // Best of keeping s1 or buying at current price
        s2 = max(s2, s1 + prices[i]);       // Best of keeping s2 or selling after s1
        s3 = max(s3, s2 - prices[i]);       // Best of keeping s3 or buying again after s2
        s4 = max(s4, s3 + prices[i]);       // Best of keeping s4 or final sell after s3
    }

    // Return the max profit (at most two transactions), or 0 if no profit
    return max(0, s4);
}



