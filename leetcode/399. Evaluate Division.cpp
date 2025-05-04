// PROBLEM :


You are given an array of variable pairs equations and an array of real numbers values, where equations[i] = [Ai, Bi] and values[i] represent the equation Ai / Bi = values[i]. Each Ai or Bi is a string that represents a single variable.

You are also given some queries, where queries[j] = [Cj, Dj] represents the jth query where you must find the answer for Cj / Dj = ?.

Return the answers to all queries. If a single answer cannot be determined, return -1.0.

Note: The input is always valid. You may assume that evaluating the queries will not result in division by zero and that there is no contradiction.

Note: The variables that do not occur in the list of equations are undefined, so the answer cannot be determined for them.

 

Example 1:

Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
Explanation: 
Given: a / b = 2.0, b / c = 3.0
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? 
return: [6.0, 0.5, -1.0, 1.0, -1.0 ]
note: x is undefined => -1.0

Example 2:

Input: equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0], queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
Output: [3.75000,0.40000,5.00000,0.20000]
  
Example 3:

Input: equations = [["a","b"]], values = [0.5], queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
Output: [0.50000,2.00000,-1.00000,-1.00000]




// SOLUTION :


class Solution {
public:

    // DFS helper to search from 'node' to 'dest'
    void dfs(string node, string& dest,
             unordered_map<string, unordered_map<string, double>>& gr,
             unordered_set<string>& vis,
             double& ans, double temp) {

        // If node is already visited, skip to prevent cycles
        if(vis.find(node) != vis.end()) return;

        vis.insert(node); // Mark current node as visited

        // If destination is reached, store the result
        if(node == dest){
            ans = temp;
            return;
        }

        // Visit all unvisited neighbors
        for(auto ne : gr[node]){
            dfs(ne.first, dest, gr, vis, ans, temp * ne.second); // multiply path value
        }
    }

    // Build the graph from equations and values
    unordered_map<string, unordered_map<string, double>> buildGraph(
        const vector<vector<string>>& equations,
        const vector<double>& values) {

        unordered_map<string, unordered_map<string, double>> gr;

        for (int i = 0; i < equations.size(); i++) {
            string dividend = equations[i][0];
            string divisor = equations[i][1];
            double value = values[i];

            // Build bidirectional graph:
            gr[dividend][divisor] = value;           // a / b = value
            gr[divisor][dividend] = 1.0 / value;     // b / a = 1 / value
        }

        return gr;
    }

    // Solve each query using DFS
    vector<double> calcEquation(vector<vector<string>>& equations,
                                vector<double>& values,
                                vector<vector<string>>& queries) {

        // Step 1: Build the graph
        unordered_map<string, unordered_map<string, double>> gr = buildGraph(equations, values);
        vector<double> finalAns;

        // Step 2: Process each query
        for (auto query : queries) {
            string dividend = query[0];
            string divisor = query[1];

            // If either variable is not in the graph, return -1.0
            if (gr.find(dividend) == gr.end() || gr.find(divisor) == gr.end()) {
                finalAns.push_back(-1.0);
            } else {
                unordered_set<string> vis;
                double ans = -1.0; // default if no path is found
                double temp = 1.0; // start with a multiplier of 1
                dfs(dividend, divisor, gr, vis, ans, temp);
                finalAns.push_back(ans);
            }
        }

        return finalAns;
    }
};




