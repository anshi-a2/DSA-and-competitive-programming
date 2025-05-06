// PROBLEM :


A gene string can be represented by an 8-character long string, with choices from 'A', 'C', 'G', and 'T'.

Suppose we need to investigate a mutation from a gene string startGene to a gene string endGene where one mutation is defined as one single character changed in the gene string.

For example, "AACCGGTT" --> "AACCGGTA" is one mutation.
There is also a gene bank bank that records all the valid gene mutations. A gene must be in bank to make it a valid gene string.

Given the two gene strings startGene and endGene and the gene bank bank, return the minimum number of mutations needed to mutate from startGene to endGene. If there is no such a mutation, return -1.

Note that the starting point is assumed to be valid, so it might not be included in the bank.

 
Example 1:

Input: startGene = "AACCGGTT", endGene = "AACCGGTA", bank = ["AACCGGTA"]
Output: 1
  
Example 2:

Input: startGene = "AACCGGTT", endGene = "AAACGGTA", bank = ["AACCGGTA","AACCGCTA","AAACGGTA"]
Output: 2



// SOLUTION :


class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {
       unordered_set<string> valid(bank.begin(), bank.end());

        // If the end mutation is not in the bank, we can't reach it
        if (!valid.count(end)) return -1;

        // Queue for BFS traversal
        queue<string> q;
        q.push(start);

        // Track number of mutations (steps) taken
        int steps = 0;

        // All possible characters for mutation
        const vector<char> genes = {'A', 'C', 'G', 'T'};

        while (!q.empty()) {
            int levelSize = q.size();  // Number of nodes at current BFS level

            // Process all nodes (mutations) at current level
            while (levelSize--) {
                string current = q.front();
                q.pop();

                // If we've reached the target mutation, return number of steps
                if (current == end) return steps;

                // For each position in the string, try all possible mutations
                for (int i = 0; i < 8; ++i) {
                    char originalChar = current[i];
                    for (char gene : genes) {
                        if (gene == originalChar) continue; // Skip same character

                        current[i] = gene; // Mutate

                        // If mutation is valid and not visited yet
                        if (valid.count(current)) {
                            q.push(current);      // Add to queue for next level
                            valid.erase(current); // Mark as visited
                        }
                    }
                    current[i] = originalChar; // Restore original character
                }
            }

            steps++; // Finished processing one level (one mutation step)
        }

        // If end mutation is unreachable
        return -1;
    }
};



