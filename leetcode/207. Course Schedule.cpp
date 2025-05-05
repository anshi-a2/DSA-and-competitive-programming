// PROBLEM :


There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
Return true if you can finish all courses. Otherwise, return false.

Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0. So it is possible.
  
Example 2:

Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.



// SOLUTION :



// Kahn’s Algorithm for Topological Sorting:
// Kahn’s Algorithm works by repeatedly finding vertices with no incoming edges,
// removing them from the graph, and updating the incoming edges of the vertices connected from the removed removed edges.
// This process continues until all vertices have been ordered.


class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // Create graph and in-degree array
        vector<vector<int>> graph(numCourses);
        vector<int> inDegree(numCourses, 0);

        // Build graph and fill in-degree
        for (auto& pair : prerequisites) {
            int course = pair[0];
            int prereq = pair[1];
            graph[prereq].push_back(course);
            inDegree[course]++;
        }

        // Queue to store all nodes with in-degree 0 (no prerequisites)
        queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        int completed = 0;

        // Process nodes with in-degree 0
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            completed++;

            for (int neighbor : graph[curr]) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        // If all courses are completed, return true
        return completed == numCourses;
    }
};


// Explanation:

// inDegree[i] stores the number of prerequisites for course i.

// Courses with no prerequisites are pushed into a queue.

// For each course taken, reduce the in-degree of its neighbors.

// If a neighbor’s in-degree becomes zero, it’s ready to be taken next.

// If we’re able to "complete" all courses, there's no cycle; otherwise, return false.
