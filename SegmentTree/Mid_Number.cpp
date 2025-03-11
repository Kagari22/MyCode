#include <bits/stdc++.h>

// from: cpp.json
#define int long long
#define i32 __int32_t
#define i64 long long
#define i128 __int128_t
const int MOD = 1e9 + 7;
using namespace std;

const int MAXN = 1e5 + 5;
vector<int> values(MAXN);
int cnt[MAXN * 40], L[MAXN * 40], R[MAXN * 40], root[MAXN];
int arr[MAXN], idx = 0;

void build(int &node, int l, int r) {
    node = ++idx;
    cnt[node] = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(L[node], l, mid);
    build(R[node], mid + 1, r);
}

void update(int &node, int prev, int l, int r, int pos) {
    node = ++idx;
    L[node] = L[prev], R[node] = R[prev];
    cnt[node] = cnt[prev] + 1;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (pos <= mid) update(L[node], L[prev], l, mid, pos);
    else update(R[node], R[prev], mid + 1, r, pos);
}

int query(int u, int v, int l, int r, int k) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    int count = cnt[L[v]] - cnt[L[u]];
    if (count >= k) return query(L[u], L[v], l, mid, k);
    else return query(R[u], R[v], mid + 1, r, k - count);
}

void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        values[i] = arr[i];
    }
    
    sort(values.begin() + 1, values.begin() + n + 1);
    values.erase(unique(values.begin() + 1, values.begin() + n + 1), values.end());
    
    build(root[0], 1, n);
    
    for (int i = 1; i <= n; i++) {
        int pos = lower_bound(values.begin() + 1, values.end(), arr[i]) - values.begin();
        update(root[i], root[i - 1], 1, n, pos);
    }
    
    while (q--) {
        int L, R;
        cin >> L >> R;
        int k = (R - L + 1) / 2 + 1;
        int pos = query(root[L - 1], root[R], 1, n, k);
        cout << values[pos] << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while (t--) {
        solve();
    }

    return 0;
}