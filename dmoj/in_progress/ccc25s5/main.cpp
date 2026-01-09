#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct TreeNode {
    ll total;
    ll finish;
    ll capacity;
};

struct SegmentTree {
    int n;
    vector<TreeNode> tree;

    SegmentTree(int size) : n(size), tree(4 * size) {}

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            tree[node] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) update(2 * node, l, mid, idx, val);
        else update(2 * node + 1, mid + 1, r, idx, val);

        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int idx, int val) {
        update(1, 0, n - 1, idx, val);
    }

    // Query: max in [ql, qr]
    int query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return INT_MIN; // no overlap
        if (ql <= l && r <= qr) return tree[node]; // full overlap
        int mid = (l + r) / 2;
        int left = query(2 * node, l, mid, ql, qr);
        int right = query(2 * node + 1, mid + 1, r, ql, qr);
        return max(left, right);
    }

    int query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};

int main() {
    vector<int> arr = {1, 5, 2, 4, 3};
    SegmentTree st(arr.size());
    st.build(arr);

    cout << st.query(1, 3) << "\n"; // max in [1,3] = 5
    st.update(2, 10);               // arr[2] = 10
    cout << st.query(1, 3) << "\n"; // now max in [1,3] = 10
}
