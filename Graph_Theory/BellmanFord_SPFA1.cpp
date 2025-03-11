#include <bits/stdc++.h>

// https://www.luogu.com.cn/problem/P1938
#define INF 1e18
#define int long long
using namespace std;

const int MAXN = 1000;

int d, p, c, f, s;
int n;

vector<vector<pair<int, int>>> adj(MAXN);

vector<int> dist(MAXN, 0); 
vector<int> cnt(MAXN, 0);    
vector<bool> enter(MAXN, false);

void addEdge(int u, int v, int w) {
    adj[u].emplace_back(v, w);
}

void spfa() {
    queue<int> q;
    
    // 初始在 s 城市 就在初始化 s
    q.push(s);
    dist[s] = d;
    enter[s] = true;
    cnt[s]++;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        enter[u] = false;
        
        for (auto &[v, w] : adj[u]) {
            if (dist[v] < dist[u] + w) {
                dist[v] = dist[u] + w;
                if (!enter[v]) {
                    q.push(v);
                    enter[v] = true;
                }
            }
        }
    }
}

void solve() {
    // 初始在 s 城市
    cin >> d >> p >> c >> f >> s;

    n = c;
    
    for (int i = 1; i <= p; i++) {
        int u, v;
        cin >> u >> v;
        // 点权转化成边权
        addEdge(u, v, d);  
    }

    for (int i = 1; i <= f; i++) {
        int j, k, t;
        cin >> j >> k >> t;
        addEdge(j, k, d - t);  
    }

    spfa();

    int ans = 0;

    for (int i = 1; i <= n; i++) {
        ans = max(ans, dist[i]);
    }

    cout << ans << '\n';
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
