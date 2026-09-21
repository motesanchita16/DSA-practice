#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> result(k, 0);

        // dp[r] = number of subarrays ending at previous index
        // whose product % k == r
        vector<long long> dp(k, 0);

        for (int num : nums) {
            int rem = num % k;

            vector<long long> newDp(k, 0);

            // Start a new subarray with current element
            newDp[rem]++;

            // Extend all previous subarrays
            for (int r = 0; r < k; r++) {
                int newRem = (r * rem) % k;
                newDp[newRem] += dp[r];
            }

            // Add current subarrays to final answer
            for (int r = 0; r < k; r++) {
                result[r] += newDp[r];
            }

            dp = newDp;
        }

        return result;
    }
};