// PROBLEM :


There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
Return the ordering of courses you should take to finish all courses. If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.

 

Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: [0,1]
Explanation: There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1].
Example 2:

Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
Output: [0,2,1,3]
Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0.
So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3].
Example 3:

Input: numCourses = 1, prerequisites = []
Output: [0]


// SOLUTION :


class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        // Adjacency list to store graph: each course -> list of courses that depend on it
        vector<vector<int>> adj(numCourses);
        
        // Indegree array to count how many prerequisites each course has
        vector<int> indegree(numCourses, 0);
        
        // Build the graph and populate the indegree array
        for (auto& pre : prerequisites) {
            adj[pre[1]].push_back(pre[0]); // pre[1] -> pre[0] (prereq -> course)
            indegree[pre[0]]++;            // Increase indegree of the course
        }

        // Queue to hold courses with no prerequisites (indegree 0)
        queue<int> q;
        for (int i = 0; i < numCourses; ++i)
            if (indegree[i] == 0)
                q.push(i); // Push course with no prerequisites into queue
        
        vector<int> order; // Stores the final course order

        // Process courses with no prerequisites
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            order.push_back(node); // Add current course to the order

            // Decrease the indegree of dependent courses
            for (int neighbor : adj[node]) {
                indegree[neighbor]--;        // One prerequisite has been satisfied
                if (indegree[neighbor] == 0) // If all prerequisites are satisfied
                    q.push(neighbor);        // Add course to queue
            }
        }

        // If all courses are processed, return the valid order
        // Otherwise, return an empty list (cycle detected)
        return (order.size() == numCourses) ? order : vector<int>();
    }
};



