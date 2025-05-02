// PROBLEM :


Given the head of a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list. Return the linked list sorted as well.

Example 1:

Input: head = [1,2,3,3,4,4,5]
Output: [1,2,5]
  
Example 2:

Input: head = [1,1,1,2,3]
Output: [2,3]


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
public:
    ListNode* deleteDuplicates(ListNode* head) {
         if(head==nullptr||head->next==nullptr)return head;
        ListNode* temp = head;
        ListNode* dummy = new ListNode(-1);
        ListNode* prev = dummy ;
        prev->next = head;
        while(temp!=nullptr&&temp->next!=nullptr){
            if(temp->next->val==temp->val){
                int v = temp->val;
                while(temp!=nullptr){
                    if(temp->val==v)temp = temp->next;
                    else break ;
                }
                prev->next = temp;
            }
            else{
                prev = temp ;
                temp = temp->next;
            }
        }
        return dummy->next;
    }
};


