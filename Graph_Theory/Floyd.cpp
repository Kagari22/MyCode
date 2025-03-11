#include <bits/stdc++.h>
#define INF 1e18
#define int long long
using namespace std;

const int MAXN = 500; // 最大节点数
int dist[MAXN][MAXN];
int n, m; // n 为节点数，m 为边数

void Floyd() {
    for (int k = 0; k < n; k++) {         // 中间节点
        for (int i = 0; i < n; i++) {     // 起点
            for (int j = 0; j < n; j++) { // 终点
                if (dist[i][k] < INF && dist[k][j] < INF) { 
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

void Init() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) dist[i][j] = 0; // 自己到自己距离为 0
            else dist[i][j] = INF;      // 初始为无穷大
        }
    }
}

void solve() {
    cin >> n >> m;

    Init(); 

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--; 
        dist[u][v] = min(dist[u][v], w); // 处理重边
    }

    Floyd();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF) cout << "INF ";
            else cout << dist[i][j] << " ";
        }
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    
    while (t--) {
        solve();
    }

    return 0;
}
