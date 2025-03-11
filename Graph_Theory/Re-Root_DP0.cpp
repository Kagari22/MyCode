#include <bits/stdc++.h>

// 换根 DP
// https://www.luogu.com.cn/problem/P3478
// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // sum[i]: i 节点去往子树所有节点的距离和
    vector<int> siz(n + 1), sum(n + 1), dp(n + 1);

    auto dfs1 = [&](auto&& dfs1, int u, int fa) -> void {
        for (auto v : g[u]) {
            if (v != fa) {
                dfs1(dfs1, v, u);
            }
        }

        siz[u] = 1;
        sum[u] = 0;

        for (auto v : g[u]) {
            if (v != fa) {
                siz[u] += siz[v];
                sum[u] += sum[v] + siz[v];
            }
        }
    };

    auto dfs2 = [&](auto&& dfs2, int u, int fa) -> void {
        for (auto v : g[u]) {
            if (v != fa) {
                dp[v] = dp[u] + n - 2 * siz[v];
                dfs2(dfs2, v, u);
            }
        }
    };

    dfs1(dfs1, 1, 0);

    dp[1] = sum[1];

    dfs2(dfs2, 1, 0);

    int mx = -INF, ans = 0;

    for (int i = 1; i <= n; i++) {
        if (dp[i] > mx) {
            mx = dp[i];
            ans = i;
        }
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