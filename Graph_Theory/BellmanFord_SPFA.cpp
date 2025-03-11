#include <bits/stdc++.h>

// https://www.luogu.com.cn/problem/P3385
using namespace std;

/*  给定一个n个点的有向图，
请求出图中是否存在从顶点1出发能到达的负环。
负环的定义是 : —条边权之和为负数的回路。*/

#define MAXN 2001

vector<vector<pair<int, int>>> adj(MAXN);
vector<int> dist(MAXN, INT_MAX);         
vector<int> updateCnt(MAXN, 0);          
vector<bool> enter(MAXN, false);         

void init(int n) {
    adj.assign(n + 1, vector<pair<int, int>>());
    dist.assign(n + 1, INT_MAX);
    updateCnt.assign(n + 1, 0);
    enter.assign(n + 1, false);
}

void addEdge(int u, int v, int w) {
    adj[u].emplace_back(v, w);
    if (w >= 0) {
        adj[v].emplace_back(u, w); 
    }
}

bool spfa(int n) {
    queue<int> q;
    dist[1] = 0;
    updateCnt[1]++;
    q.push(1);
    enter[1] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        enter[u] = false;

        for (auto &[v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (!enter[v]) {
                    if (updateCnt[v]++ == n) {
                        return true;
                    }
                    q.push(v);
                    enter[v] = true;
                }
            }
        }
    }
    return false;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        int n, m;
        cin >> n >> m; 
        init(n);      

        for (int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w; 
            addEdge(u, v, w);
        }

        cout << (spfa(n) ? "YES" : "NO") << "\n";
    }
    return 0;
}
