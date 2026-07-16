/*
Problem: 3867. Sum of GCD of Formed Pairs
Platform: LeetCode
Difficulty: Medium
Date: 16-07-2026

Approach:
1. Compute prefix maximum.
2. Calculate gcd(nums[i], prefixMax).
3. Store values in prefixGcd.
4. Sort prefixGcd.
5. Pair smallest with largest.
6. Add gcd of each pair.

Time Complexity: O(n log n)
Space Complexity: O(n)
*/

class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        int n  = nums.size();
        vector<int> prefixGcd;

        int mx = 0;

        for(int x : nums){
            mx = max(mx, x);
            prefixGcd.push_back(std::gcd(x, mx));
        }

        sort (prefixGcd.begin(), prefixGcd.end());

        long long ans = 0;
        int l = 0, r = n -1;

        while(l<r){
            ans += std::gcd(prefixGcd[l], prefixGcd[r]);
            l++;
            r--;
        }
        return ans;
    }
};