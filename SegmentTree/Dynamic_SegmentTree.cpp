#include <bits/stdc++.h>

// 动态开点线段树
// from: cpp.json
#define INF 1e18
#define int long long
using namespace std;

int n, m;
const int MAXN = 114514;

int cnt;
int Left[MAXN], Right[MAXN], sum[MAXN], add[MAXN];

void up(int h, int l, int r) {
    sum[h] = sum[l] + sum[r];
}

void lazy(int i, int v, int n) {
    sum[i] += v * n;
    add[i] += v;
}

void down(int i, int ln, int rn) {
    if (add[i] != 0) {
        if (Left[i] == 0) {
            Left[i] = ++cnt;
        }
        if (Right[i] == 0) {
            Right[i] = ++cnt;
        }
        lazy(Left[i], add[i], ln);
        lazy(Right[i], add[i], rn);
        add[i] = 0;
    }
}

void Add(int jobl, int jobr, int jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        lazy(i, jobv, r - l + 1);
    } else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if (jobl <= mid) {
            if (Left[i] == 0) {
                Left[i] = ++cnt;
            }
            Add(jobl, jobr, jobv, l, mid, Left[i]);
        }
        if (jobr > mid) {
            if (Right[i] == 0) {
                Right[i] = ++cnt;
            }
            Add(jobl, jobr, jobv, mid + 1, r, Right[i]);
        }
        up(i, Left[i], Right[i]);
    }
}

int query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return sum[i];
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    int ans = 0;
    if (jobl <= mid && Left[i] != 0) {
        ans += query(jobl, jobr, l, mid, Left[i]);
    }
    if (jobr > mid && Right[i] != 0) {
        ans += query(jobl, jobr, mid + 1, r, Right[i]);
    }
    return ans;
}

void init() {
    for (int i = 1; i <= cnt; i++) {
        Left[i] = 0;
        Right[i] = 0;
        sum[i] = 0;
        add[i] = 0;
    }
}

void solve(){
    cin >> n >> m;

    cnt = 1;

    for (int i = 1; i <= m; i++) {
        int op, jobl, jobr, jobv;
        cin >> op;
        if (op == 1) {
            cin >> jobl >> jobr >> jobv;
            Add(jobl, jobr, jobv, 1, n, 1);
        } else {
            cin >> jobl >> jobr;
            cout << query(jobl, jobr, 1, n, 1) << '\n'; 
        }
    }

    init();
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
