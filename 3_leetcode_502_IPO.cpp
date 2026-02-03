/*
========================================================
LeetCode 502 — IPO
Greedy + Heap Based Solutions
========================================================
Problem:
Maximize capital by selecting at most k projects.
Each project has a required capital and gives a profit.

--------------------------------------------------------
Approach 1: Two Heaps (Capital Heap + Profit Heap)
--------------------------------------------------------
Idea:
- Use a min-heap to track projects by required capital.
- Use a max-heap to select the most profitable project
  among currently affordable projects.

Algorithm:
1. Push all projects into a min-heap ordered by capital.
2. Repeat k times:
   - Move all affordable projects into a max-profit heap.
   - Pick the project with maximum profit.
3. Return final capital.

Time Complexity:  O(n log n)
Space Complexity: O(n)
========================================================
*/

class Solution {
public:
    typedef pair<int,int> P;

    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        int n = capital.size();

        // Max-heap to choose project with maximum profit
        priority_queue<int> maxProfit;

        // Min-heap to track projects by minimum capital requirement
        priority_queue<P, vector<P>, greater<P>> minCapital;

        // Push all projects into capital heap
        for(int i = 0; i < n; i++){
            minCapital.push({capital[i], profits[i]});
        }

        // Select at most k projects
        while(k--) {
            // Move all affordable projects to profit heap
            while(!minCapital.empty() && minCapital.top().first <= w) {
                maxProfit.push(minCapital.top().second);
                minCapital.pop();
            }

            // If no project is affordable, stop
            if(maxProfit.empty()) break;

            // Choose most profitable project
            w += maxProfit.top();
            maxProfit.pop();
        }

        return w;
    }
};


/*
========================================================
Approach 2: Sorting + Max Heap
--------------------------------------------------------
Idea:
- Sort projects by required capital.
- Use a max-heap to select best profit among
  affordable projects.

Algorithm:
1. Store (capital, profit) pairs and sort by capital.
2. Iterate k times:
   - Add all affordable projects to max-heap.
   - Pick project with maximum profit.
3. Return final capital.

Time Complexity:  O(n log n)
Space Complexity: O(n)
========================================================
*/

class Solution {
public:
    int findMaximizedCapital(int k, int capitalAvailable, vector<int>& profits, vector<int>& capital) {
        int n = profits.size();

        vector<pair<int,int>> projects;
        for(int i = 0; i < n; i++) {
            projects.push_back({capital[i], profits[i]});
        }

        // Sort projects by capital requirement
        sort(projects.begin(), projects.end());

        priority_queue<int> maxProfit;
        int i = 0;

        while(k--) {
            // Add all affordable projects
            while(i < n && projects[i].first <= capitalAvailable) {
                maxProfit.push(projects[i].second);
                i++;
            }

            if(maxProfit.empty()) break;

            capitalAvailable += maxProfit.top();
            maxProfit.pop();
        }

        return capitalAvailable;
    }
};
