// Approach - 1 : Sliding Window using Max Heap & Min Heap
//
// Time Complexity:
//   O(n log n)
//   - Each element is pushed once into both heaps
//   - Each push/pop operation takes O(log n)
//   - Overall complexity becomes O(n log n)
//
// Space Complexity:
//   O(n)
//   - In the worst case, both heaps can store up to n elements

class Solution {
public:
    typedef pair<int,int> P;

    int longestSubarray(vector<int>& nums, int limit) {
        int n = nums.size();
        priority_queue<P, vector<P>> maxheap;                  // max element
        priority_queue<P, vector<P>, greater<P>> minheap;      // min element

        int i = 0, j = 0;
        int max_length = 0;

        while (j < n) {
            maxheap.push({nums[j], j});
            minheap.push({nums[j], j});

            while (maxheap.top().first - minheap.top().first > limit) {
                i = min(maxheap.top().second, minheap.top().second) + 1;

                while (maxheap.top().second < i) maxheap.pop();
                while (minheap.top().second < i) minheap.pop();
            }

            max_length = max(max_length, j - i + 1);
            j++;
        }
        return max_length;
    }
};
// Approach - 2 : Sliding Window using Multiset
//
// Time Complexity:
//   O(n log n)
//   - Each element is inserted once into the multiset → O(log n)
//   - Each element is erased once from the multiset → O(log n)
//   - Total operations over n elements → O(n log n)
//
// Space Complexity:
//   O(n)
//   - Multiset can store up to n elements in the worst case

class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        int n = nums.size();
        multiset<int> st;

        int i = 0, j = 0;
        int max_length = 0;

        while (j < n) {
            st.insert(nums[j]);

            while (*st.rbegin() - *st.begin() > limit) {
                st.erase(st.find(nums[i]));
                i++;
            }

            max_length = max(max_length, j - i + 1);
            j++;
        }
        return max_length;
    }
};
