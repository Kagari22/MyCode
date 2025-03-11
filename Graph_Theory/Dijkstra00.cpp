#include <bits/stdc++.h>

// 一个顶点到其余顶点的最短路
#define int long long
using namespace std;

const int MAXN = 100001;
const int MAXM = 200001;
const int INF = 0x3f3f3f3f3f3f3f3f;

// 链式前向星
int head[MAXN];
int nextt[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt;

// 反向索引堆
int heap[MAXN];
int wheree[MAXN];
int heapSize;
int dist[MAXN];
int n, m, s;

void build() {
    cnt = 1;
    heapSize = 0;
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
        wheree[i] = -1;
        dist[i] = INF;
    }
}

void addEdge(int u, int v, int w) {
    nextt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void swapp(int i, int j) {
    int temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
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
        for (int ei = head[v]; ei > 0; ei = nextt[ei]) {
            addOrUpdateOrIgnore(to[ei], dist[v] + weight[ei]);
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
        addEdge(u, v, w);
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
