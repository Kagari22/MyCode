#include <bits/stdc++.h>

// from: cpp.json
#define INF 1e18
#define int long long
using namespace std;

class SegTree {  // 区间更新,加减，维护最值, GCD
public:
    SegTree(int n) {
        this->n = n;
        mx.resize(n << 2);
        mn.resize(n << 2);
        gcdVal.resize(n << 2); 
        addTag.resize(n << 2);
        change.resize(n << 2);
        updateTag.resize(n << 2);
        build(1, n, 1);
    }

    void set(int i, long long v) {  // 单点更新
        update(i, i, v, 1, n, 1);
    }

    void set(int l, int r, long long v) {  // 区间更新
        if (l > r)
            return;
        update(l, r, v, 1, n, 1);
    }

    void add(int i, long long v) {  // 单点加
        add(i, i, v, 1, n, 1);
    }

    void add(int l, int r, long long v) {  // 区间加
        if (l > r)
            return;
        add(l, r, v, 1, n, 1);
    }

    long long get(int i) {  // 单点查询
        return queryMax(i, i, 1, n, 1);
    }

    long long queryMax(int l, int r) {  // 区间查询最大值
        if (l > r)
            return MIN;
        return queryMax(l, r, 1, n, 1);
    }

    long long queryMin(int l, int r) {  // 区间查询最小值
        if (l > r)
            return MAX;
        return queryMin(l, r, 1, n, 1);
    }

    long long queryGCD(int l, int r) {  // 区间查询GCD
        if (l > r)
            return 0;  
        return queryGCD(l, r, 1, n, 1);
    }

private:
    static const long long MAX = 0x3f3f3f3f3f3f3f3f;
    static const long long MIN = 0;
    int n;
    std::vector<long long> mx, mn, gcdVal, change, addTag;
    std::vector<bool> updateTag;

    void up(int i) {
        mx[i] = std::max(mx[i << 1], mx[i << 1 | 1]);
        mn[i] = std::min(mn[i << 1], mn[i << 1 | 1]);
        gcdVal[i] = std::gcd(gcdVal[i << 1], gcdVal[i << 1 | 1]);
    }

    void build(int l, int r, int i) {
        if (l == r)
            mx[i] = mn[i] = gcdVal[i] = 0;  
        else {
            int mid = (l + r) >> 1;
            build(l, mid, i << 1);
            build(mid + 1, r, i << 1 | 1);
            up(i);
        }
        updateTag[i] = false;
        change[i] = 0;
        addTag[i] = 0;
    }

    void down(int l, int r, int i) {
        if (updateTag[i]) {
            int mid = (l + r) >> 1;
            lazy_update(l, mid, change[i], i << 1);
            lazy_update(mid + 1, r, change[i], i << 1 | 1);
            updateTag[i] = false;
        }
        if (addTag[i]) {
            int mid = (l + r) >> 1;
            lazy_add(l, mid, addTag[i], i << 1);
            lazy_add(mid + 1, r, addTag[i], i << 1 | 1);
            addTag[i] = 0;
        }
    }

    void lazy_add(int l, int r, long long v, int i) {
        mx[i] += v;
        mn[i] += v;
        
        if (v != 0) {
            gcdVal[i] = std::gcd(gcdVal[i], v); 
        }

        addTag[i] += v;
    }

    void lazy_update(int l, int r, long long v, int i) {
        mx[i] = v;
        mn[i] = v;
        gcdVal[i] = v; 
        change[i] = v;
        updateTag[i] = true;
        addTag[i] = 0;
    }

    void update(int L, int R, long long v, int l, int r, int i) {
        if (L <= l && r <= R)
            lazy_update(l, r, v, i);
        else {
            down(l, r, i);
            int mid = (l + r) >> 1;
            if (L <= mid)
                update(L, R, v, l, mid, i << 1);
            if (R > mid)
                update(L, R, v, mid + 1, r, i << 1 | 1);
            up(i);
        }
    }

    void add(int L, int R, long long v, int l, int r, int i) {
        if (L <= l && r <= R)
            lazy_add(l, r, v, i);
        else {
            down(l, r, i);
            int mid = (l + r) >> 1;
            if (L <= mid)
                add(L, R, v, l, mid, i << 1);
            if (R > mid)
                add(L, R, v, mid + 1, r, i << 1 | 1);
            up(i);
        }
    }

    long long queryMax(int L, int R, int l, int r, int i) {
        if (L <= l && R >= r)
            return mx[i];
        else {
            down(l, r, i);
            int mid = (l + r) >> 1;
            long long res = MIN;
            if (L <= mid)
                res = std::max(res, queryMax(L, R, l, mid, i << 1));
            if (R > mid)
                res = std::max(res, queryMax(L, R, mid + 1, r, i << 1 | 1));
            return res;
        }
    }

    long long queryMin(int L, int R, int l, int r, int i) {
        if (L <= l && R >= r)
            return mn[i];
        else {
            down(l, r, i);
            int mid = (l + r) >> 1;
            long long res = MAX;
            if (L <= mid)
                res = std::min(res, queryMin(L, R, l, mid, i << 1));
            if (R > mid)
                res = std::min(res, queryMin(L, R, mid + 1, r, i << 1 | 1));
            return res;
        }
    }

    long long queryGCD(int L, int R, int l, int r, int i) {
        if (L <= l && R >= r)
            return gcdVal[i];
        else {
            down(l, r, i);
            int mid = (l + r) >> 1;
            long long res = 0;
            if (L <= mid)
                res = std::gcd(res, queryGCD(L, R, l, mid, i << 1));
            if (R > mid)
                res = std::gcd(res, queryGCD(L, R, mid + 1, r, i << 1 | 1));
            return res;
        }
    }
};

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    SegTree seg(n);

    for (int i = 1; i <= n; i++) {
        seg.set(i, a[i - 1]);
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        solve();
    }

    return 0;
}