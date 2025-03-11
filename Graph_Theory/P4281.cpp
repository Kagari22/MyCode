#include <bits/stdc++.h>

// https://www.luogu.com.cn/problem/P4281
// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

const int MAXN = 500001;
int power;
vector<int> g[MAXN];
int deep[MAXN];
int stjump[MAXN][20];

int Log2(int n) {
    int ans = 0;
    while ((1LL << ans) <= (n >> 1LL)) {
        ans++;
    }
    return ans;
}

void dfs(int u, int f) {
    deep[u] = deep[f] + 1;
    stjump[u][0] = f;

    for (int p = 1; p <= power; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }

    for (auto v : g[u]) {
        if (v != f) {
            dfs(v, u);
        }
    }
}

int LCA(int a, int b) {
    if (deep[a] < deep[b]) {
        swap(a, b);
    }

    for (int p = power; p >= 0; p--) {
        if (deep[stjump[a][p]] >= deep[b]) {
            a = stjump[a][p];
        }
    }

    if (a == b) {
        return a;
    }

    for (int p = power; p >= 0; p--) {
        if (stjump[a][p] != stjump[b][p]) {
            a = stjump[a][p];
            b = stjump[b][p];
        }
    }

    return stjump[a][0];
}

void solve() {
    int n, m;
    cin >> n >> m;

    power = Log2(n);

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);

    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        int h1 = LCA(a, b), h2 = LCA(a, c), h3 = LCA(b, c);
        int high = h1 != h2 ? (deep[h1] < deep[h2] ? h1 : h2) : h1;
        int low = h1 != h2 ? (deep[h1] > deep[h2] ? h1 : h2) : h3;

        int together = low;
        int cost = deep[a] + deep[b] + deep[c] - deep[high] * 2 - deep[low];

        cout << together << ' ' << cost << '\n';
    }
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