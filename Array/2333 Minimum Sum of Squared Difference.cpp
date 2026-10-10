
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        long long k = (long long)k1 + k2;
        vector<int> freq(100001, 0);
        long long total = 0;

        for (int i = 0; i < nums1.size(); i++) {
            int d = abs(nums1[i] - nums2[i]);
            freq[d]++;
            total += d;
        }

        if (k >= total) return 0;

        for (int d = 100000; d > 0 && k > 0; d--) {
            if (freq[d] == 0) continue;

            long long count = freq[d];
            long long nextLevel = d - 1;
            long long cost = count * (d - nextLevel);

            if (k >= cost) {
                freq[nextLevel] += freq[d];
                freq[d] = 0;
                k -= cost;
            } else {
                long long fullLevels = k / count;
                long long remainder = k % count;

                freq[d] -= remainder;
                freq[d - 1] += remainder;

                if (fullLevels > 0) {
                    freq[d - fullLevels] += freq[d];
                    freq[d] = 0;
                }
                break;
            }
        }

        long long ans = 0;

        for (int d = 1; d <= 100000; d++) {
            ans += 1LL * d * d * freq[d];
        }

        return ans;
    }
};
