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
    ListNode* rec(ListNode* head, int k) {
        if (!head) return nullptr;
        
        int c = k;
        ListNode* curr = head;
        ListNode* prev = nullptr;
        ListNode* next = nullptr;
        
        while (curr && c > 0) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
            c--;
        }
        
        if (c > 0) {  // If remaining nodes are less than k, reverse again to restore
            curr = prev;
            prev = nullptr;
            next = nullptr;
            
            while (curr) {
                next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            }
            return prev;
        }
        
        head->next = rec(curr, k);
        return prev;
    }
    
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        return rec(head, k);
    }
};


