// APPROACH - 1
// Time Complexity: O(n log n)
//   - Sorting the entire array takes O(n log n)
// Space Complexity: O(1) [Ignoring sort recursion stack]
//   - No extra data structure used (in-place sort)
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(begin(nums),end(nums),greater<int>());
        return nums[k-1];
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// APPROACH - 2
// Time Complexity: O(n log k)
//   - Each insertion/removal in heap costs log k
//   - Performed for n elements
// Space Complexity: O(k)
//   - Heap stores at most k elements
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int,vector<int>,greater<int>>minheap;
        for(int i=0;i<nums.size();i++){
            minheap.push(nums[i]);
            if(minheap.size()>k)    minheap.pop();
        }
        return minheap.top();
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// APPROACH - 3 (Quickselect)
// Average Time Complexity: O(n)
//   - Each partition reduces search space
// Worst Case Time Complexity: O(n^2)
//   - Happens when pivot is always the smallest/largest
// Space Complexity: O(1)
//   - In-place partitioning, no extra space used
class Solution {
public:
    int partition_algo(vector<int>& nums,int l, int r){
        int P=nums[l];
        int i=l+1;
        int j=r;
        while(i<=j){
            if(nums[i]<P&&nums[j]>P){
                swap(nums[i],nums[j]);
                i++;
                j--;
            }
            if(nums[i]>=P)   i++;
            if(nums[j]<=P)   j--;
        }
        swap(nums[j],nums[l]);
        return j;
    }
    int findKthLargest(vector<int>& nums, int k) {
        int n=nums.size();
        int L=0;
        int R=n-1;
        int pivot_idx=0;
        while(true){
            pivot_idx=partition_algo(nums,L,R);
            if(pivot_idx==k-1)  break;
            else if(pivot_idx>k-1)  R=pivot_idx-1;
            else    L=pivot_idx+1;
        }
        return nums[pivot_idx];
    }
};
