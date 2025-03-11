#include <bits/stdc++.h>

// from: cpp.json
#define INF 1e18
#define int long long
using namespace std;

class SegTree { 
public:
    SegTree(int n) {
        this->n = n;
        mx.resize(n << 2);
        mn.resize(n << 2);
        sum.resize(n << 2);  
        // gcdVal.resize(n << 2); 
        addTag.resize(n << 2);
        change.resize(n << 2);
        updateTag.resize(n << 2);
        build(1, n, 1);
    }

    void set(int i, long long v) {
        update(i, i, v, 1, n, 1);
    }

    void set(int l, int r, long long v) {  
        if (l > r)
            return;
        update(l, r, v, 1, n, 1);
    }

    void add(int i, long long v) { 
        add(i, i, v, 1, n, 1);
    }

    void add(int l, int r, long long v) {  
        if (l > r)
            return;
        add(l, r, v, 1, n, 1);
    }

    long long get(int i) {  
        return queryMax(i, i, 1, n, 1);
    }

    long long queryMax(int l, int r) { 
        if (l > r)
            return MIN;
        return queryMax(l, r, 1, n, 1);
    }

    long long queryMin(int l, int r) {  
        if (l > r)
            return MAX;
        return queryMin(l, r, 1, n, 1);
    }

    long long querySum(int l, int r) {  
        if (l > r)
            return 0;
        return querySum(l, r, 1, n, 1);
    }

    // 找区间内的第一个 >= x 的数，并更新为 -1，返回这个数的下标
    long long find_first_bigger(int l, int r, int x) {
        return find_first_bigger_than_x(1, l, r, x);
    }

private:
    static const long long MAX = 0x3f3f3f3f3f3f3f3f;
    static const long long MIN = -0x3f3f3f3f3f3f3f3f;
    int n;
    vector<long long> mx, mn, sum, change, addTag, gcdVal;
    vector<bool> updateTag;

    void up(int i) {
        mx[i] = std::max(mx[i << 1], mx[i << 1 | 1]);
        mn[i] = std::min(mn[i << 1], mn[i << 1 | 1]);
        sum[i] = sum[i << 1] + sum[i << 1 | 1];  
    }

    void build(int l, int r, int i) {
        if (l == r) {
            mx[i] = mn[i] = sum[i] = 0;
        } else {
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
        sum[i] += (r - l + 1) * v;  
        addTag[i] += v;
    }

    void lazy_update(int l, int r, long long v, int i) {
        mx[i] = v;
        mn[i] = v;
        sum[i] = (r - l + 1) * v;  
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

    long long querySum(int L, int R, int l, int r, int i) {
        if (L <= l && R >= r)
            return sum[i];
        else {
            down(l, r, i);
            int mid = (l + r) >> 1;
            long long res = 0;
            if (L <= mid)
                res += querySum(L, R, l, mid, i << 1);
            if (R > mid)
                res += querySum(L, R, mid + 1, r, i << 1 | 1);
            return res;
        }
    }

    long long find_first_bigger_than_x(int o, int l, int r, int x) {
        if (mx[o] < x) { // 区间没有 >= x 的数
            return -1;
        }
        if (l == r) {
            mx[o] = -1; // 更新为 -1，表示不能放水果
            return l;
        }
        int m = (l + r) / 2;
        int i = find_first_bigger_than_x(o * 2, l, m, x); // 先递归左子树
        if (i < 0) { // 左子树没找到
            i = find_first_bigger_than_x(o * 2 + 1, m + 1, r, x); // 再递归右子树
        }
        mx[o] = max(mx[o * 2], mx[o * 2 + 1]);
        return i;
    }
};

void solve() {
    
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