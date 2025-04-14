// PROBLEM :

Given the head of a linked list, return the list after sorting it in ascending order.

Input: head = [4,2,1,3]
Output: [1,2,3,4]


// SOLUTION :


class Solution {
public:
    ListNode* merge(ListNode* list1, ListNode* list2) {

        // O(1)
        ListNode* c = new ListNode(-1);
        ListNode* tempc = c;

        while (list1 != NULL && list2 != NULL) {
            if (list1->val >= list2->val) {
                tempc->next = list2;
                list2 = list2->next;
                tempc = tempc->next;
            } else {
                tempc->next = list1;
                list1 = list1->next;
                tempc = tempc->next;
            }
        }
        if (list1 == NULL) {
            tempc->next = list2;
        } else {
            tempc->next = list1;
        }

        return c->next;
    }

    ListNode* sortList(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        if(head == NULL || head->next == NULL) return head;

        // Find left Middle
        while (fast->next != NULL && fast->next->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode* a = head;
        ListNode* b = slow->next;
        //disconnect the left half
        slow->next = NULL;

        a = sortList(a);
        b = sortList(b);

        ListNode* ans = merge(a, b);
        return ans;
    }
};
