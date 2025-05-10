// PROBLEM :


You are given an integer array prices where prices[i] is the price of a given stock on the ith day, and an integer k.

Find the maximum profit you can achieve. You may complete at most k transactions: i.e. you may buy at most k times and sell at most k times.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).


Example 1:

Input: k = 2, prices = [2,4,1]
Output: 2
Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.
Example 2:

Input: k = 2, prices = [3,2,6,5,0,3]
Output: 7
Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.



// SOLUTION :


class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n == 0 || k == 0) return 0;

        // If k >= n/2, then it's equivalent to unlimited transactions.
        // Optimize with simpler greedy approach.
        if (k >= n / 2) {
            int profit = 0;
            for (int i = 1; i < n; ++i) {
                if (prices[i] > prices[i - 1]) {
                    profit += prices[i] - prices[i - 1];
                }
            }
            return profit;
        }

        // buy[i]: The minimum effective price for the i-th transaction buy
        // sell[i]: The maximum profit for the i-th transaction sell
        vector<int> buy(k, INT_MAX);
        vector<int> sell(k, 0);

        for (auto &p : prices) {
            // First transaction
            buy[0] = min(buy[0], p);            // Lowest price to buy
            sell[0] = max(sell[0], p - buy[0]); // Max profit after selling

            // Remaining transactions
            for (int i = 1; i < k; i++) {
                // Buy i-th stock: deduct profit made from previous sell
                buy[i] = min(buy[i], p - sell[i - 1]);
                // Sell i-th stock: update max profit for i-th transaction
                sell[i] = max(sell[i], p - buy[i]);
            }
        }

        // Final profit after k transactions
        return sell[k - 1];
    }
};





