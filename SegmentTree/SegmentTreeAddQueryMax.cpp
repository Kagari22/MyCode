#include <bits/stdc++.h>

// from: cpp.json
#define int long long
#define ll long long
const int MOD = 1e9 + 7;
using namespace std;

const int MAXN = 100001;

int arr[MAXN];
int Max[MAXN << 2];
int add[MAXN << 2];

void up(int i) {
    Max[i] = max(Max[i << 1], Max[i << 1 | 1]);
}

void lazy(int i, int v) {
    Max[i] += v;
    add[i] += v;
}

void down(int i) {
    if (add[i] != 0) {
        lazy(i << 1, add[i]);
        lazy(i << 1 | 1, add[i]);
        add[i] = 0;
    }
}

void build(int l, int r, int i) {
    if (l == r) {
        Max[i] = arr[l];
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
    add[i] = 0;
}

void addRange(int jobl, int jobr, int jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        lazy(i, jobv);
    } else {
        down(i);
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            addRange(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            addRange(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

int query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return Max[i];
    }
    down(i);
    int mid = (l + r) >> 1;
    int ans = INT_MIN;
    if (jobl <= mid) {
        ans = max(ans, query(jobl, jobr, l, mid, i << 1));
    }
    if (jobr > mid) {
        ans = max(ans, query(jobl, jobr, mid + 1, r, i << 1 | 1));
    }
    return ans;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 1000;
    build(1, n, 1);
    int jobl = 2, jobr = 4;
    // jobl 要寻找的左边界 jobr 要寻找的右边界
    int ans1 = query(jobl, jobr, 1, n, 1);

    return 0;
}