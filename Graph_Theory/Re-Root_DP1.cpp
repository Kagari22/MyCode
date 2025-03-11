#include <bits/stdc++.h>

// 换根 DP
// https://codeforces.com/problemset/problem/1187/E
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

    vector<int> siz(n + 1), dp(n + 1);

    auto dfs1 = [&](auto&& dfs1, int u, int fa) -> void {
        siz[u] = 1;
        for (auto v : g[u]) {
            if (v != fa) {
                dfs1(dfs1, v, u);
                siz[u] += siz[v];
                dp[u] += dp[v];
            }
        }
        dp[u] += siz[u];
    };

    // 染 v 时，增加 n - siz[v]
    // 染 u 时，减少 siz[v]
    auto dfs2 = [&](auto&& dfs2, int u, int fa) -> void {
        for (auto v : g[u]) {
            if (v != fa) {
                dp[v] = dp[u] + n - 2 * siz[v];
                dfs2(dfs2, v, u);
            }
        }
    };

    dfs1(dfs1, 1, 0);

    dfs2(dfs2, 1, 0);

    int ans = 0;

    for (int i = 1; i <= n; i++) {
        ans = max(ans, dp[i]);
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