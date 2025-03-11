#include <bits/stdc++.h>

// from: cpp.json
#define INF 1e18
#define int long long
using namespace std;

class SegmentTree {
public:
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        treeXor.resize(4 * n);
        treeOr.resize(4 * n);
        lazyXor.resize(4 * n, 0);
        build(arr, 0, 0, n - 1);
    }

    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            treeXor[node] = arr[start];
            treeOr[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2 * node + 1, start, mid);
            build(arr, 2 * node + 2, mid + 1, end);
            treeXor[node] = treeXor[2 * node + 1] ^ treeXor[2 * node + 2];
            treeOr[node] = treeOr[2 * node + 1] | treeOr[2 * node + 2];
        }
    }

    void update(int l, int r, int value) {
        update(0, 0, n - 1, l, r, value);
    }

    void update(int node, int start, int end, int l, int r, int value) {
        if (lazyXor[node] != 0) {
            treeXor[node] ^= lazyXor[node];
            if (start != end) {
                lazyXor[2 * node + 1] ^= lazyXor[node];
                lazyXor[2 * node + 2] ^= lazyXor[node];
            }
            lazyXor[node] = 0; 
        }
        if (r < start || end < l) {
            return;
        }
        if (l <= start && end <= r) {
            treeXor[node] ^= value;
            if (start != end) {
                lazyXor[2 * node + 1] ^= value;
                lazyXor[2 * node + 2] ^= value;
            }
            return;
        }

        int mid = (start + end) / 2;
        update(2 * node + 1, start, mid, l, r, value);
        update(2 * node + 2, mid + 1, end, l, r, value);
        treeXor[node] = treeXor[2 * node + 1] ^ treeXor[2 * node + 2];
    }

    int queryXor(int l, int r) {
        return queryXor(0, 0, n - 1, l, r);
    }

    int queryXor(int node, int start, int end, int l, int r) {
        if (lazyXor[node] != 0) {
            treeXor[node] ^= lazyXor[node];
            if (start != end) {
                lazyXor[2 * node + 1] ^= lazyXor[node];
                lazyXor[2 * node + 2] ^= lazyXor[node];
            }
            lazyXor[node] = 0;
        }
        if (r < start || end < l) {
            return 0; 
        }
        if (l <= start && end <= r) {
            return treeXor[node];
        }
        int mid = (start + end) / 2;
        int left = queryXor(2 * node + 1, start, mid, l, r);
        int right = queryXor(2 * node + 2, mid + 1, end, l, r);
        return left ^ right;
    }

    int queryOr(int l, int r) {
        return queryOr(0, 0, n - 1, l, r);
    }

    int queryOr(int node, int start, int end, int l, int r) {
        if (lazyXor[node] != 0) {
            treeXor[node] ^= lazyXor[node];
            if (start != end) {
                lazyXor[2 * node + 1] ^= lazyXor[node];
                lazyXor[2 * node + 2] ^= lazyXor[node];
            }
            lazyXor[node] = 0; 
        }

        if (r < start || end < l) {
            return 0;
        }
        if (l <= start && end <= r) {
            return treeOr[node];
        }
        int mid = (start + end) / 2;
        int left = queryOr(2 * node + 1, start, mid, l, r);
        int right = queryOr(2 * node + 2, mid + 1, end, l, r);
        return left | right;
    }

private:
    vector<int> treeXor; 
    vector<int> treeOr;  
    vector<int> lazyXor; 
    int n;               
};

void solve(){
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    SegmentTree segtree(a);
    for (int i = 0; i < q; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r, v;
            cin >> l >> r >> v;
            segtree.update(l - 1, r - 1, v); 
        } else {
            int l, r;
            cin >> l >> r;
            l--; r--;
            int Xor = segtree.queryXor(l, r);
            int Or = segtree.queryOr(l, r);
            cout << abs(Xor - Or) << '\n';
        }
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