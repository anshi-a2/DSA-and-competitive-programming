// PROBLEM :

Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

The overall run time complexity should be O(log (m+n)).

Example 1:

Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.

Example 2:

Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.



// SOLUTION :


class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int m = nums2.size();
        int i = 0, j = 0, m1 = 0, m2 = 0;

        // Find median.
        for (int count = 0; count <= (n + m) / 2; count++) {
            m2 = m1;
            if (i != n && j != m) {
                if (nums1[i] > nums2[j]) {
                    m1 = nums2[j++];
                } else {
                    m1 = nums1[i++];
                }
            } else if (i < n) {
                m1 = nums1[i++];
            } else {
                m1 = nums2[j++];
            }
        }

        // Check if the sum of n and m is odd.
        if ((n + m) % 2 == 1) {
            return static_cast<double>(m1);
        } else {
            double ans = static_cast<double>(m1) + static_cast<double>(m2);
            return ans / 2.0;
        }
    }
};


// SOLUTION 02 (using binary search : 0(log(min(n, m))):


Consider the first array is smaller. If first array is greater, then swap the arrays to make sure that the first array is smaller.
We mainly maintain two sets in this algorithm by doing binary search in the smaller array. Let mid1 be the partition of the smaller array. The first set contains elements from 0 to (mid1 – 1) from smaller array and mid2 = ((n + m + 1) / 2 – mid1) elements from the greater array to make sure that the first set has exactly (n+m+1)/2 elements. The second set contains remaining half elements.
Our target is to find a point in both arrays such that all elements in the first set are smaller than all elements in the elements in the other set (set that contains elements from right side). For this we validate the partitions using the same way as we did in Median of two sorted arrays of same size.


class Solution {
public:
    double findMedianSortedArrays(vector<int>& a, vector<int>& b) {
        int n = a.size(), m = b.size();
	
  	// If a[] has more elements, then call medianOf2 
  	// with reversed parameters
    if (n > m)
        return findMedianSortedArrays(b, a);
  
    int lo = 0, hi = n;
    while (lo <= hi) {
        int mid1 = (lo + hi) / 2;
        int mid2 = (n + m + 1) / 2 - mid1;

        // Find elements to the left and right of partition in a[]
        int l1 = (mid1 == 0 ? INT_MIN : a[mid1 - 1]);
        int r1 = (mid1 == n ? INT_MAX : a[mid1]);

        // Find elements to the left and right of partition in b[]
        int l2 = (mid2 == 0 ? INT_MIN : b[mid2 - 1]);
        int r2 = (mid2 == m ? INT_MAX : b[mid2]);

        // If it is a valid partition
        if (l1 <= r2 && l2 <= r1) {
          
          	// If the total elements are even, then median is 
          	// the average of two middle elements
            if ((n + m) % 2 == 0)
                return (max(l1, l2) + min(r1, r2)) / 2.0;
          
          	// If the total elements are odd, then median is 
         	// the middle element
            else
                return max(l1, l2);
        }

        // Check if we need to take lesser elements from a[]
        if (l1 > r2)
            hi = mid1 - 1;
      
        // Check if we need to take more elements from a[]
        else
            lo = mid1 + 1;
    }
    return 0;
    }
};




