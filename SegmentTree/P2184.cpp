#include <bits/stdc++.h>

// https://www.luogu.com.cn/problem/P2184
// from: cpp.json
#define int long long
using namespace std;

const int MAXN = 100001;
int bombStarts[MAXN << 2];
int bombEnds[MAXN << 2];

void up(int i) {
    bombStarts[i] = bombStarts[i << 1] + bombStarts[i << 1 | 1];
    bombEnds[i] = bombEnds[i << 1] + bombEnds[i << 1 | 1];
}

void build(int l, int r, int i) {
    if (l < r) {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
    }
    bombStarts[i] = 0;
    bombEnds[i] = 0;
}

void add(int jobt, int jobi, int l, int r, int i) {
    if (l == r) {
        if (jobt == 0) {
            bombStarts[i]++;
        } else {
            bombEnds[i]++;
        }
    } else {
        int mid = (l + r) >> 1;
        if (jobi <= mid) {
            add(jobt, jobi, l, mid, i << 1);
        } else {
            add(jobt, jobi, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

int query(int jobt, int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return jobt == 0 ? bombStarts[i] : bombEnds[i];
    } else {
        int mid = (l + r) >> 1;
        int ans = 0;
        if (jobl <= mid) {
            ans += query(jobt, jobl, jobr, l, mid, i << 1);
        }
        if (jobr > mid) {
            ans += query(jobt, jobl, jobr, mid + 1, r, i << 1 | 1);
        }
        return ans;
    }
}

void solve(){
    int n, m;
    cin >> n >> m;
    build(1, n, 1);
    for (int i = 1; i <= m; i++) {
        int op, jobl, jobr;
        cin >> op >> jobl >> jobr;
        if (op == 1) {
            add(0, jobl, 1, n, 1);
            add(1, jobr, 1, n, 1);
        } else {
            int s = query(0, 1, jobr, 1, n, 1);
            int e = jobl == 1 ? 0 : query(1, 1, jobl - 1, 1, n, 1);
            cout << s - e << "\n";
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