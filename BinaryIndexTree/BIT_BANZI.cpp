#include <bits/stdc++.h>

// 树状数组模版
// https://codeforces.com/contest/597/problem/C
// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

const int MAXN = 1e5 + 5;

struct BIT {
    int tree[MAXN];

    int lowbit(int i) {
        return i & -i;
    }

    void add(int i, int v) {
        while (i <= MAXN) {
            tree[i] += v;
            i += lowbit(i);
        }
    }

    int sum(int i) {
        int ans = 0;
        while (i) {
            ans += tree[i];
            i -= lowbit(i);
        }
        return ans;
    }

    int range(int l, int r) {
        return sum(r) - sum(l - 1);
    }
} b[15];

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    k++;

    // dp[i][j]: 1 到 i 中长度为 j 的 LIS
    vector<vector<int>> dp(n + 1, vector<int>(k + 1));

    int ans = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= min(i, k); j++) {
            if (j == 1) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = b[j - 1].sum(a[i] - 1);
            }
            b[j].add(a[i], dp[i][j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        ans += dp[i][k];
    }

    cout << ans << '\n';
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