#include <bits/stdc++.h>

// https://www.luogu.com.cn/problem/P3870
// from: cpp.json
#define int long long
#define i32 __int32_t
#define i64 long long
#define i128 __int128_t
const int MOD = 1e9 + 7;
using namespace std;

const int MAXN = 100001;
int light[MAXN << 2];
bool rev[MAXN << 2];

void up(int i) {
    light[i] = light[i << 1] + light[i << 1 | 1];
}

void lazy(int i, int n) {
    light[i] = n - light[i];
    rev[i] = !rev[i];
}

void build(int l, int r, int i) {
    if (l == r) {
        light[i] = 0;
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
    rev[i] = false;
}

void down(int i, int ln, int rn) {
    if (rev[i]) {
        lazy(i << 1, ln);
        lazy(i << 1 | 1, rn);
        rev[i] = false;
    }
}

void Reverse(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        lazy(i, r - l + 1);
    } else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if (jobl <= mid) {
            Reverse(jobl, jobr, l, mid, i << 1);
        }
        if (jobr > mid) {
            Reverse(jobl, jobr, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

int query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return light[i];
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    int ans = 0;
    if (jobl <= mid) {
        ans += query(jobl, jobr, l, mid, i << 1);
    }
    if (jobr > mid) {
        ans += query(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}

void solve(){
    int n, m;
    cin >> n >> m;
    build(1, n, 1);
    for (int i = 1; i <= m; i++) {
        int op, jobl, jobr;
        cin >> op >> jobl >> jobr;
        if (op == 0) {
            Reverse(jobl, jobr, 1, n, 1);
        } else {
            cout << query(jobl, jobr, 1, n, 1) << "\n";
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