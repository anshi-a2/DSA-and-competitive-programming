// PROBLEM :


Given the head of a linked list, rotate the list to the right by k places.

Example 1:

Input: head = [1,2,3,4,5], k = 2
Output: [4,5,1,2,3]
  
Example 2:

Input: head = [0,1,2], k = 4
Output: [2,0,1]



// SOLUTION :


/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public ListNode rotateRight(ListNode head, int k) {
        if(head == null || head.next == null) return head;
        
        // Step 1: Find the length of the linked list
        ListNode temp = head;
        int length = 0;
        while(temp != null) {
            length++;
            temp = temp.next;
        }
        
        // Step 2: Calculate the effective rotation using modulo
        int rotation = k % length;

        // Step 3: Perform the rotation for 'rotation' times
        for(int i = 0; i < rotation; i++) {
            ListNode last = head, prev = null;
            
            // Step 4: Traverse the list to find the last node
            while(last.next != null) {
                prev = last;
                last = last.next;
            }
            
            // Step 5: Perform the rotation by adjusting pointers
            last.next = head;
            prev.next = null;
            head = last;
        }
        
        return head;
    }
}



