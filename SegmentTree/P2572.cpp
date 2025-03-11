#include <bits/stdc++.h>

// https://www.luogu.com.cn/problem/P2572
/*
0 l r：将区间 [l, r] 内的所有数值设为 0。
1 l r：将区间 [l, r] 内的所有数值设为 1。
2 l r：将区间 [l, r] 内的所有数值取反，即将所有的 0 变成 1，所有的 1 变成 0。
3 l r：查询区间 [l, r] 内有多少个 1。
4 l r：查询区间 [l, r] 内最多有多少个连续的 1。
*/
// from: cpp.json
#define int long long
using namespace std;

const int MAXN = 100001;
int arr[MAXN << 2];
int sum[MAXN << 2];
int len0[MAXN << 2];
int pre0[MAXN << 2];
int suf0[MAXN << 2];
int len1[MAXN << 2];
int pre1[MAXN << 2];
int suf1[MAXN << 2];
int change[MAXN << 2];
bool update[MAXN << 2];
bool rev[MAXN << 2];

void up(int i, int ln, int rn) {
    int l = i << 1;
    int r = i << 1 | 1;
    sum[i] = sum[l] + sum[r];
    len0[i] = max({len0[l], len0[r], suf0[l] + pre0[r]});
    pre0[i] = len0[l] < ln ? pre0[l] : (pre0[l] + pre0[r]);
    suf0[i] = len0[r] < rn ? suf0[r] : (suf0[l] + suf0[r]);
    len1[i] = max({len1[l], len1[r], suf1[l] + pre1[r]});
    pre1[i] = len1[l] < ln ? pre1[l] : (pre1[l] + pre1[r]);
    suf1[i] = len1[r] < rn ? suf1[r] : (suf1[l] + suf1[r]);
}

void updateLazy(int i, int v, int n) {
    sum[i] = v * n;
    len0[i] = pre0[i] = suf0[i] = (v == 0 ? n : 0);
    len1[i] = pre1[i] = suf1[i] = (v == 1 ? n : 0);
    change[i] = v;
    update[i] = true;
    rev[i] = false;
}

void reverseLazy(int i, int n) {
    sum[i] = n - sum[i];
    swap(len0[i], len1[i]);
    swap(pre0[i], pre1[i]);
    swap(suf0[i], suf1[i]);
    rev[i] = !rev[i];
}


void down(int i, int ln, int rn) {
    if (update[i]) {
        updateLazy(i << 1, change[i], ln);
        updateLazy(i << 1 | 1, change[i], rn);
        update[i] = false;
    }
    if (rev[i]) {
        reverseLazy(i << 1, ln);
        reverseLazy(i << 1 | 1, rn);
        rev[i] = false;
    }
}

void build(int l, int r, int i) {
    if (l == r) {
        sum[i] = arr[l];
        len0[i] = pre0[i] = suf0[i] = (arr[l] == 0 ? 1 : 0);
        len1[i] = pre1[i] = suf1[i] = (arr[l] == 1 ? 1 : 0);
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i, mid - l + 1, r - mid);
    }
    update[i] = false;
    rev[i] = false;
}

void Update(int jobl, int jobr, int jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        updateLazy(i, jobv, r - l + 1);
    } else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if (jobl <= mid) {
            Update(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            Update(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i, mid - l + 1, r - mid);
    }
}

void Reverse(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        reverseLazy(i, r - l + 1);
    } else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if (jobl <= mid) {
            Reverse(jobl, jobr, l, mid, i << 1);
        }
        if (jobr > mid) {
            Reverse(jobl, jobr, mid + 1, r, i << 1 | 1);
        }
        up(i, mid - l + 1, r - mid);
    }
}

int querySum(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return sum[i];
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    int ans = 0;
    if (jobl <= mid) {
        ans += querySum(jobl, jobr, l, mid, i << 1);
    }
    if (jobr > mid) {
        ans += querySum(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}

vector<int> queryLongest(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return { len1[i], pre1[i], suf1[i] };
    } else {
        int mid = (l + r) >> 1;
        int ln = mid - l + 1;
        int rn = r - mid;
        down(i, ln, rn);
        if (jobr <= mid) {
            return queryLongest(jobl, jobr, l, mid, i << 1);
        }
        if (jobl > mid) {
            return queryLongest(jobl, jobr, mid + 1, r, i << 1 | 1);
        }
        auto l3 = queryLongest(jobl, jobr, l, mid, i << 1);
        auto r3 = queryLongest(jobl, jobr, mid + 1, r, i << 1 | 1);
        int llen = l3[0], lpre = l3[1], lsuf = l3[2];
        int rlen = r3[0], rpre = r3[1], rsuf = r3[2];
        int len = max({llen, rlen, lsuf + rpre});
        int pre = llen < mid - max(jobl, l) + 1 ? lpre : (lpre + rpre);
        int suf = rlen < min(r, jobr) - mid ? rsuf : (lsuf + rsuf);
        return {len, pre, suf};
    }
}

void solve(){
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    build(1, n, 1);
    for (int i = 1; i <= m; i++) {
        int op, jobl, jobr;
        cin >> op >> jobl >> jobr;
        jobl++, jobr++;
        if (op == 0) {
            Update(jobl, jobr, 0, 1, n, 1);
        } else if (op == 1) {
            Update(jobl, jobr, 1, 1, n, 1);
        } else if (op == 2) {
            Reverse(jobl, jobr, 1, n, 1);
        } else if (op == 3) {
            cout << querySum(jobl, jobr, 1, n, 1) << '\n';
        } else {
            cout << queryLongest(jobl, jobr, 1, n, 1)[0] << '\n';
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1; 

    while(t--) {
        solve();
    }

    return 0;
}
