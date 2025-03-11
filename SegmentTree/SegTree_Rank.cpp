#include <bits/stdc++.h>

// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

class SegmentTree {
public:
    SegmentTree(const vector<int>& data) {
        n = data.size();
        tree.resize(4 * n);
        build(data, 0, 0, n - 1);
    }

    // 查询 [l, r] 区间内小于等于 x 的数的个数
    int query(int l, int r, int x) {
        return query(0, 0, n - 1, l, r, x);
    }

private:
    int n;
    vector<vector<int>> tree;

    void build(const vector<int>& data, int node, int start, int end) {
        if (start == end) {
            tree[node].push_back(data[start]);
        } else {
            int mid = (start + end) / 2;
            build(data, 2 * node + 1, start, mid);
            build(data, 2 * node + 2, mid + 1, end);
            merge(tree[2 * node + 1].begin(), tree[2 * node + 1].end(),
                    tree[2 * node + 2].begin(), tree[2 * node + 2].end(),
                    back_inserter(tree[node]));
        }
    }

    // 查询区间 [l, r] 内小于等于 x 的数的个数
    int queryLesser(int node, int start, int end, int l, int r, int x) {
        if (r < start || end < l) {
            return 0;
        }
        if (l <= start && end <= r) {
            return upper_bound(tree[node].begin(), tree[node].end(), x) - tree[node].begin();
        }
        int mid = (start + end) / 2;
        return query(2 * node + 1, start, mid, l, r, x) +
                query(2 * node + 2, mid + 1, end, l, r, x);
    }
};

void solve() {
    SegmentTree seg(5);
    seg.set(1, 16);
    seg.set(2, 8);
    seg.set(3, 8);
    seg.set(4, 20);

    int ans = seg.queryLesser(1, 4, 17);
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;

    while(t--){
        solve();
    }

    return 0;
}