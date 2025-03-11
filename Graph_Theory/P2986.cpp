#include <bits/stdc++.h>

// https://www.luogu.com.cn/problem/P2986
// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

const int MAXN = 100001;
int n;
int cow[MAXN];
int cowSum = 0;
int best = LLONG_MAX, center;
int siz[MAXN], path[MAXN];
vector<vector<array<int, 2>>> g(MAXN);

void solve() {
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> cow[i];
    }    

    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});  
        g[v].push_back({u, w});
    }

    for (int i = 1; i <= n; i++) {
        cowSum += cow[i];
    }

    auto dfs = [&](auto&& dfs, int u, int fa) -> void {
        siz[u] = cow[u];
        
        for (auto& edge : g[u]) {
            int v = edge[0]; 
            if (v != fa) {
                dfs(dfs, v, u);
            }
        }

        int maxsub = 0;

        for (auto& edge : g[u]) {
            int v = edge[0];  
            if (v != fa) {
                siz[u] += siz[v];
                maxsub = max(maxsub, siz[v]);
            }
        }

        maxsub = max(maxsub, cowSum - siz[u]);

        if (maxsub < best) {
            best = maxsub;
            center = u;
        }
    };

    // 找重心
    dfs(dfs, 1, 0);

    path[center] = 0;

    auto setPath = [&](auto&& setPath, int u, int fa) -> void {
        for (auto& edge : g[u]) {
            int v = edge[0];  
            int w = edge[1];  
            if (v != fa) {
                path[v] = path[u] + w;
                setPath(setPath, v, u);
            }
        }
    };

    setPath(setPath, center, 0);

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += cow[i] * path[i];
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