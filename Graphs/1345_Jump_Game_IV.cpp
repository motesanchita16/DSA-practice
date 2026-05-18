#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();

        if (n == 1) return 0;

        unordered_map<int, vector<int>> mp;

        // Store all indices of each value
        for (int i = 0; i < n; i++) {
            mp[arr[i]].push_back(i);
        }

        queue<int> q;
        vector<bool> visited(n, false);

        q.push(0);
        visited[0] = true;

        int steps = 0;

        while (!q.empty()) {
            int size = q.size();

            while (size--) {
                int index = q.front();
                q.pop();

                if (index == n - 1) {
                    return steps;
                }

                // Move to index + 1
                if (index + 1 < n && !visited[index + 1]) {
                    visited[index + 1] = true;
                    q.push(index + 1);
                }

                // Move to index - 1
                if (index - 1 >= 0 && !visited[index - 1]) {
                    visited[index - 1] = true;
                    q.push(index - 1);
                }

                // Move to all indices having same value
                int value = arr[index];

                if (mp.find(value) != mp.end()) {
                    for (int nextIndex : mp[value]) {
                        if (!visited[nextIndex]) {
                            visited[nextIndex] = true;
                            q.push(nextIndex);
                        }
                    }

                    // Important optimization to avoid TLE
                    mp.erase(value);
                }
            }

            steps++;
        }

        return -1;
    }
};