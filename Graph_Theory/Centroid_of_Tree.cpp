#include <bits/stdc++.h>

// https://www.luogu.com.cn/problem/U104609
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

    vector<int> maxsub(n + 1);
    vector<int> siz(n + 1);

    int best = INF;

    auto dfs = [&](auto&& dfs, int u, int fa) -> void {
        siz[u] = 1;
        maxsub[u] = 0;

        for (auto v : g[u]) {
            if (v != fa) {
                dfs(dfs, v, u);
                siz[u] += siz[v];
                maxsub[u] = max(maxsub[u], siz[v]);
            }
        }

        maxsub[u] = max(maxsub[u], n - siz[u]);
    };

    dfs(dfs, 1, 0);

    vector<int> ans;
    
    for (int i = 1; i <= n; i++) {
        if (maxsub[i] <= n / 2) {
            ans.push_back(i);
        }
    }

    sort(ans.begin(), ans.end());

    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
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