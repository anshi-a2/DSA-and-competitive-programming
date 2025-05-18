// PROBLEM :


Given the head of a linked list, reverse the nodes of the list k at a time, and return the modified list.

k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes, in the end, should remain as it is.

You may not alter the values in the list's nodes, only nodes themselves may be changed.


Example 1:

Input: head = [1,2,3,4,5], k = 2
Output: [2,1,4,3,5]
  
Example 2:

Input: head = [1,2,3,4,5], k = 3
Output: [3,2,1,4,5]



// SOLUTION :


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
private:
    // Recursive helper function to reverse nodes in groups of k
    ListNode* rec(ListNode* head, int k) {
        if (!head) return nullptr; // Base case: empty list

        int c = k;
        ListNode* curr = head;
        ListNode* prev = nullptr;
        ListNode* next = nullptr;

        // Try to reverse k nodes
        while (curr && c > 0) {
            next = curr->next;    // Save next node
            curr->next = prev;    // Reverse current node's pointer
            prev = curr;          // Move prev to current
            curr = next;          // Move to next node
            c--;
        }

        // If we reversed fewer than k nodes, restore the original order
        if (c > 0) {
            // Reverse again to undo the partial reversal
            curr = prev;
            prev = nullptr;
            next = nullptr;

            while (curr) {
                next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            }

            return prev; // Return the head of the restored list
        }

        // Recursively call for the remaining list starting from current
        head->next = rec(curr, k);

        // Return the new head of the reversed segment
        return prev;
    }

public:
    // Main function to reverse nodes in k-group
    ListNode* reverseKGroup(ListNode* head, int k) {
        return rec(head, k);
    }
};




