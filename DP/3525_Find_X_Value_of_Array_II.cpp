#include <bits/stdc++.h>
using namespace std;

class Solution {
    struct Node {
        int product;
        long long cnt[5];

        Node() {
            product = 1;
            for (int i = 0; i < 5; i++) {
                cnt[i] = 0;
            }
        }
    };

    int n, k;
    vector<Node> tree;

    Node mergeNodes(const Node& left, const Node& right) {
        Node res;

        // Product of the complete segment
        res.product = (left.product * right.product) % k;

        // Prefixes completely inside the left segment
        for (int r = 0; r < k; r++) {
            res.cnt[r] += left.cnt[r];
        }

        // Prefixes that use the complete left segment
        // and then a prefix of the right segment
        for (int r = 0; r < k; r++) {
            int newRem = (left.product * r) % k;
            res.cnt[newRem] += right.cnt[r];
        }

        return res;
    }

    void build(int node, int l, int r, vector<int>& nums) {
        if (l == r) {
            int rem = nums[l] % k;

            tree[node].product = rem;
            tree[node].cnt[rem] = 1;

            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid, nums);
        build(node * 2 + 1, mid + 1, r, nums);

        tree[node] = mergeNodes(
            tree[node * 2],
            tree[node * 2 + 1]
        );
    }

    void update(int node, int l, int r, int index, int value) {
        if (l == r) {
            int rem = value % k;

            tree[node] = Node();
            tree[node].product = rem;
            tree[node].cnt[rem] = 1;

            return;
        }

        int mid = (l + r) / 2;

        if (index <= mid) {
            update(node * 2, l, mid, index, value);
        } else {
            update(node * 2 + 1, mid + 1, r, index, value);
        }

        tree[node] = mergeNodes(
            tree[node * 2],
            tree[node * 2 + 1]
        );
    }

    Node query(int node, int l, int r, int ql, int qr) {
        // Completely inside query range
        if (ql <= l && r <= qr) {
            return tree[node];
        }

        int mid = (l + r) / 2;

        // Query completely in right side
        if (ql > mid) {
            return query(node * 2 + 1, mid + 1, r, ql, qr);
        }

        // Query completely in left side
        if (qr <= mid) {
            return query(node * 2, l, mid, ql, qr);
        }

        // Query overlaps both sides
        Node left = query(node * 2, l, mid, ql, qr);
        Node right = query(node * 2 + 1, mid + 1, r, ql, qr);

        return mergeNodes(left, right);
    }

public:
    vector<int> resultArray(
        vector<int>& nums,
        int k,
        vector<vector<int>>& queries
    ) {
        this->n = nums.size();
        this->k = k;

        tree.resize(4 * n);

        build(1, 0, n - 1, nums);

        vector<int> result;

        for (auto& q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Persistent update
            update(1, 0, n - 1, index, value);

            // Query nums[start ... n-1]
            Node ans = query(
                1,
                0,
                n - 1,
                start,
                n - 1
            );

            result.push_back(ans.cnt[x]);
        }

        return result;
    }
};