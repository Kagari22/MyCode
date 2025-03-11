#include <bits/stdc++.h>

// 邻接表版本
#define int long long
using namespace std;

constexpr int MAXN = 100001;
constexpr int INF = 0x3f3f3f3f3f3f3f3f;

vector<pair<int, int>> adj[MAXN]; 

int heap[MAXN];
int wheree[MAXN];
int heapSize;
int dist[MAXN];
int n, m, s;

void build() {
    heapSize = 0;
    for (int i = 1; i <= n; i++) {
        wheree[i] = -1;
        dist[i] = INF;
    }
}

void swapp(int i, int j) {
    swap(heap[i], heap[j]);
    wheree[heap[i]] = i;
    wheree[heap[j]] = j;
}

void heapInsert(int i) {
    while (i > 0 && dist[heap[i]] < dist[heap[(i - 1) / 2]]) {
        swapp(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

void heapify(int i) {
    int l = i * 2 + 1;
    while (l < heapSize) {
        int best = (l + 1 < heapSize && dist[heap[l + 1]] < dist[heap[l]]) ? l + 1 : l;
        best = dist[heap[best]] < dist[heap[i]] ? best : i;
        if (best == i) break;
        swapp(best, i);
        i = best;
        l = i * 2 + 1;
    }
}

int popp() {
    int ans = heap[0];
    swapp(0, --heapSize);
    heapify(0);
    wheree[ans] = -2; 
    return ans;
}

void addOrUpdateOrIgnore(int v, int w) {
    if (wheree[v] == -1) {
        heap[heapSize] = v;
        wheree[v] = heapSize++;
        dist[v] = w;
        heapInsert(wheree[v]);
    } else if (wheree[v] >= 0 && w < dist[v]) {
        dist[v] = w;
        heapInsert(wheree[v]);
    }
}

bool isEmpty() {
    return heapSize == 0;
}

void dijkstra() {
    dist[s] = 0;
    addOrUpdateOrIgnore(s, 0);
    while (!isEmpty()) {
        int v = popp();
        for (const auto& [neighbor, weight] : adj[v]) {
            addOrUpdateOrIgnore(neighbor, dist[v] + weight);
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> s;
    build();
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
    }
    dijkstra();
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INF) cout << "INF";
        else cout << dist[i];
        if (i < n) cout << " ";
    }
    cout << endl;
    return 0;
}
