#include <bits/stdc++.h>

// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

class SegmentTree {
    vector<int> mx;

    // 初始化线段树
    void build(const vector<int>& a, int o, int l, int r) {
        if (l == r) {
            mx[o] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(a, o * 2, l, m);
        build(a, o * 2 + 1, m + 1, r);
        maintain(o);
    }

public:
    SegmentTree(vector<int>& a) {
        int n = a.size();
        mx.resize(n << 2);
        build(a, 1, 0, n - 1);
    }

    // 找区间内的第一个 >= x 的数，并更新为 -1，返回这个数的下标
    int find_first_bigger_than_x(int o, int l, int r, int x) {
        if (mx[o] < x) { // 区间没有 >= x 的数
            return -1;
        }
        if (l == r) {
            mx[o] = -1; // 更新为 -1，表示不能放水果
            return l;
        }
        int m = (l + r) / 2;
        int i = find(o * 2, l, m, x); // 先递归左子树
        if (i < 0) { // 左子树没找到
            i = find(o * 2 + 1, m + 1, r, x); // 再递归右子树
        }
        mx[o] = max(mx[o * 2], mx[o * 2 + 1]);
        return i;
    }

    int find_first_bigger(int l, int r, int x) {
        return find_first_bigger_than_x(1, l, r, x);
    }
};

void solve() {
    
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}