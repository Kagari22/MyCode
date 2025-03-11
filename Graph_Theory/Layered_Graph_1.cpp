#include <bits/stdc++.h>

// 分层图
// https://www.luogu.com.cn/problem/P4568
// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

struct Info {
    int v, w, cnt;
    bool operator<(const Info& other) const {
        return w > other.w; 
    }
};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    int s, t;
    cin >> s >> t;

    vector<vector<pair<int, int>>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    vector<vector<int>> dist(n + 1, vector<int>(k + 1, INF));
    bool visited[n + 1][k + 1];
    memset(visited, false, sizeof(visited));

    dist[s][0] = 0;

    priority_queue<Info> pq;

    pq.push(Info{s, 0, 0});

    while (!pq.empty()) {
        auto x = pq.top();
        pq.pop();

        int u = x.v, cur_cnt = x.cnt;

        if (visited[u][cur_cnt]) {
            continue;
        }
        visited[u][cur_cnt] = true;

        for (const auto& [v, w] : g[u]) {
            if (cur_cnt < k && dist[v][cur_cnt + 1] > dist[u][cur_cnt]) {
                dist[v][cur_cnt + 1] = dist[u][cur_cnt];
                pq.push(Info{v, dist[v][cur_cnt + 1], cur_cnt + 1});
            }
            if (dist[v][cur_cnt] > dist[u][cur_cnt] + w) {
                dist[v][cur_cnt] = dist[u][cur_cnt] + w;
                pq.push(Info{v, dist[v][cur_cnt], cur_cnt});
            }
        }
    } 

    int ans = INF;

    for (int i = 0; i <= k; i++) {
        ans = min(ans, dist[t][i]);
    }

    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}