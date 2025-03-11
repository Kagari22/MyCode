#include <bits/stdc++.h>

// 线段树模板 优化常数版
// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

class SegTree {
#pragma region 内部结构
private:
    struct Node {
        long long mx, mn, sum;
        long long add, change;
        bool has_change;
        
        Node() : mx(0), mn(0), sum(0), add(0), change(0), has_change(false) {}
    };
    
    vector<Node> tree;
    int n;
    static const long long Inf = LLONG_MAX;
    static const long long NInf = LLONG_MIN;
    
    inline void push_up(int rt) {
        tree[rt].mx = max(tree[rt<<1].mx, tree[rt<<1|1].mx);
        tree[rt].mn = min(tree[rt<<1].mn, tree[rt<<1|1].mn);
        tree[rt].sum = tree[rt<<1].sum + tree[rt<<1|1].sum;
    }

    inline void apply_change(int rt, long long v, int len) {
        tree[rt].mx = tree[rt].mn = v;
        tree[rt].sum = v * len;
        tree[rt].change = v;
        tree[rt].has_change = true;
        tree[rt].add = 0; 
    }

    inline void apply_add(int rt, long long v, int len) {
        tree[rt].mx += v;
        tree[rt].mn += v;
        tree[rt].sum += v * len;
        tree[rt].add += v;
    }

    inline void push_down(int rt, int l, int r) {
        int mid = (l + r) >> 1;
        int left_len = mid - l + 1;
        int right_len = r - mid;

        if (tree[rt].has_change) {
            apply_change(rt<<1, tree[rt].change, left_len);
            apply_change(rt<<1|1, tree[rt].change, right_len);
            tree[rt].has_change = false;
        }
        if (tree[rt].add) {
            apply_add(rt<<1, tree[rt].add, left_len);
            apply_add(rt<<1|1, tree[rt].add, right_len);
            tree[rt].add = 0;
        }
    }
#pragma endregion

public:
    SegTree(int size) : n(size) {
        tree.resize(n << 2);
        build(1, n, 1);
    }

    void build(int l, int r, int rt) {
        if (l == r) {
            tree[rt].mx = tree[rt].mn = tree[rt].sum = 0;
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, rt<<1);
        build(mid+1, r, rt<<1|1);
        push_up(rt);
    }

    void range_update(int L, int R, long long v, int l=1, int r=0, int rt=1) {
        if (r == 0) r = n; 
        if (R < L) return;
        
        if (L <= l && r <= R) {
            apply_change(rt, v, r - l + 1);
            return;
        }
        push_down(rt, l, r);
        int mid = (l + r) >> 1;
        if (L <= mid) range_update(L, R, v, l, mid, rt<<1);
        if (R > mid) range_update(L, R, v, mid+1, r, rt<<1|1);
        push_up(rt);
    }

    void range_add(int L, int R, long long v, int l=1, int r=0, int rt=1) {
        if (r == 0) r = n;
        if (R < L) return;
        
        if (L <= l && r <= R) {
            apply_add(rt, v, r - l + 1);
            return;
        }
        push_down(rt, l, r);
        int mid = (l + r) >> 1;
        if (L <= mid) range_add(L, R, v, l, mid, rt<<1);
        if (R > mid) range_add(L, R, v, mid+1, r, rt<<1|1);
        push_up(rt);
    }

    long long query_max(int L, int R, int l=1, int r=0, int rt=1) {
        if (r == 0) r = n;
        if (R < L) return NInf;
        
        if (L <= l && r <= R) return tree[rt].mx;
        push_down(rt, l, r);
        int mid = (l + r) >> 1;
        long long res = NInf;
        if (L <= mid) res = max(res, query_max(L, R, l, mid, rt<<1));
        if (R > mid) res = max(res, query_max(L, R, mid+1, r, rt<<1|1));
        return res;
    }

    long long query_min(int L, int R, int l=1, int r=0, int rt=1) {
        if (r == 0) r = n;
        if (R < L) return Inf;
        
        if (L <= l && r <= R) return tree[rt].mn;
        push_down(rt, l, r);
        int mid = (l + r) >> 1;
        long long res = Inf;
        if (L <= mid) res = min(res, query_min(L, R, l, mid, rt<<1));
        if (R > mid) res = min(res, query_min(L, R, mid+1, r, rt<<1|1));
        return res;
    }

    long long query_sum(int L, int R, int l=1, int r=0, int rt=1) {
        if (r == 0) r = n;
        if (R < L) return 0;
        
        if (L <= l && r <= R) return tree[rt].sum;
        push_down(rt, l, r);
        int mid = (l + r) >> 1;
        long long res = 0;
        if (L <= mid) res += query_sum(L, R, l, mid, rt<<1);
        if (R > mid) res += query_sum(L, R, mid+1, r, rt<<1|1);
        return res;
    }

    void set(int pos, long long v) { range_update(pos, pos, v); }
    void set(int l, int r, long long v) { range_update(l, r, v); }
    void add(int pos, long long v) { range_add(pos, pos, v); }
    long long get(int pos) { return query_sum(pos, pos); }
};

void solve() {
    
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