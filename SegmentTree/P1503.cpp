#include <bits/stdc++.h>

// https://www.luogu.com.cn/problem/P1503
// from: cpp.json
#define INF 1e18
#define int long long
using namespace std;

const int MAXN = 50001;
int pre[MAXN << 2];
int suf[MAXN << 2];
stack<int> stk;

void up(int l, int r, int i) {
    pre[i] = pre[i << 1];
    suf[i] = suf[i << 1 | 1];
    int mid = (l + r) >> 1;
    if (pre[i << 1] == mid - l + 1) {
        pre[i] += pre[i << 1 | 1];
    }
    if (suf[i << 1 | 1] == r - mid) {
        suf[i] += suf[i << 1];
    }
}

void build(int l, int r, int i) {
    if (l == r) {
        pre[i] = suf[i] = 1;
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(l, r, i);
    }
}

void update(int jobi, int jobv, int l, int r, int i) {
    if (l == r) {
        pre[i] = suf[i] = jobv;
    } else {
        int mid = (l + r) >> 1;
        if (jobi <= mid) {
            update(jobi, jobv, l, mid, i << 1);
        } else {
            update(jobi, jobv, mid + 1, r, i << 1 | 1);
        }
        up(l, r, i);
    }
}

int query(int jobi, int l, int r, int i) {
    if (l == r) {
        return pre[i];
    } else {
        int mid = (l + r) >> 1;
        if (jobi <= mid) {
            if (jobi > mid - suf[i << 1]) {
                return suf[i << 1] + pre[i << 1 | 1];
            } else {
                return query(jobi, l, mid, i << 1);
            }
        } else {
            if (mid + pre[i << 1 | 1] >= jobi) {
                return suf[i << 1] + pre[i << 1 | 1];
            } else {
                return query(jobi, mid + 1, r, i << 1 | 1);
            }
        }
    }
}

void solve(){
    int n, m;
    cin >> n >> m;

    build(1, n, 1);

    for (int i = 1; i <= m; i++) {
        char c;
        cin >> c;
        if (c == 'D') {
            int x;
            cin >> x;
            update(x, 0, 1, n, 1);
            stk.push(x);
        } else if (c == 'R') {
            int x = stk.top();
            stk.pop();
            update(x, 1, 1, n, 1);
        } else {
            int x;
            cin >> x;
            cout << query(x, 1, n, 1) << '\n';
        }
    }
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