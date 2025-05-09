// PROBLEM :

You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.
Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.
You may assume that you have an infinite number of each kind of coin.

Example 1:

Input: coins = [1,2,5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1
  
Example 2:

Input: coins = [2], amount = 3
Output: -1
  
Example 3:

Input: coins = [1], amount = 0
Output: 0


// SOLUTION :


class Solution {
public:
    // Returns the minimum number of coins needed to make up the given amount
    // If it's not possible, returns -1
    int coinChange(vector<int>& coins, int amount) {
        // Initialize a DP array where minCoins[i] represents the minimum number of coins to make amount i
        // Fill with a value greater than any possible minimum (amount + 1 is effectively "infinity" here)
        vector<int> minCoins(amount + 1, amount + 1);
        minCoins[0] = 0; // Base case: 0 coins needed to make amount 0

        // Compute minCoins for all amounts from 1 to 'amount'
        for (int i = 1; i <= amount; i++) {
            // Try every coin
            for (int j = 0; j < coins.size(); j++) {
                if (i - coins[j] >= 0) {
                    // If coin can be used, update the minimum
                    minCoins[i] = min(minCoins[i], 1 + minCoins[i - coins[j]]);
                }
            }
        }

        // If minCoins[amount] is still amount + 1, it means amount can't be formed
        return minCoins[amount] != amount + 1 ? minCoins[amount] : -1;
    }
};


// SOLUTION 02 (filpping the loop) :


class Solution {
public:
    // Returns the minimum number of coins needed to make up the given amount.
    // If it's not possible to form the amount with the given coins, returns -1.
    int coinChange(vector<int>& coins, int amount) {
        // Create a DP array where dp[i] represents the minimum coins to make amount i
        // Initialize all entries with amount + 1 (a value greater than any valid result)
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0; // Base case: 0 coins are needed to make amount 0

        // For each coin, update the DP table
        for (int coin : coins) {
            // Only compute for amounts >= coin
            for (int i = coin; i <= amount; ++i) {
                // Either keep current dp[i], or use this coin (1 + dp[i - coin])
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }

        // If dp[amount] wasn't updated, it means it's not possible to make up the amount
        return dp[amount] > amount ? -1 : dp[amount];
    }
};




