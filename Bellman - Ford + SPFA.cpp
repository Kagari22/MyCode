//https://www.luogu.com.cn/problem/P3385

/*  给定一个n个点的有向图，
请求出图中是否存在从顶点1出发能到达的负环。
负环的定义是 : —条边权之和为负数的回路。*/

#include <iostream>
#include <vector>
#include <limits>
#include <cstring>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

#define MAXN 2001
#define MAXM 6001
// SPFA需要
#define MAXQ 4000001

// 链式前向星建图需要
vector<int> head(MAXN, 0);

vector<int> nextArray(MAXM, 0); // Changed from "next" to "nextArray"

vector<int> to(MAXM, 0);

vector<int> weight(MAXM, 0);

int cnt;

// 源点出发到每个节点的距离表
vector<int> dist(MAXN, INT_MAX); // Changed from "distance" to "dist"

// 节点被松弛的次数
vector<int> updataCnt(MAXN, 0);

// 哪些节点被松弛了放入队列
vector<int> q(MAXQ, 0); // Changed from "queue" to "q"

int l, r;

// 节点是否已经在队列中
vector<bool> enter(MAXN, false);

void print(int n) {
	for (int i = 1; i <= n; i++) {
		printf("从源点到 顶点%d 的最短距离为:", i);
		printf("%d \n", dist[i]);
	}
	printf("\n");
}

void Init() {
	head.assign(MAXN, 0);
	nextArray.assign(MAXM, 0);
	to.assign(MAXM, 0);
	weight.assign(MAXM, 0);
	dist.assign(MAXN, INT_MAX);
	updataCnt.assign(MAXN, 0);
	q.assign(MAXQ, 0);
	enter.assign(MAXN, false);
}


void build(int n) {
	cnt = 1;
	l = r = 0;
}

void addEdge(int u, int v, int w) {
	nextArray[cnt] = head[u];
	to[cnt] = v;
	weight[cnt] = w;
	head[u] = cnt++;
}

bool spfa(int n) {
	dist[1] = 0;
	updataCnt[1]++;
	q[r++] = 1;
	enter[1] = true;
	while (l < r) {
		int u = q[l++];
		enter[u] = false;
		//从ei出发的所有边
		for (int ei = head[u], v, w; ei > 0; ei = nextArray[ei]) {
			v = to[ei];
			w = weight[ei];
			if (dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				if (!enter[v]) {
					//发现负环
					if (updataCnt[v]++ == n) {
						return true;
					}
					q[r++] = v;
					enter[v] = true;
				}
			}
		}
	}
	return false;
}

int main() {
	int T;
	cin >> T; // 读取测试数据的组数
	while (T--) {
		Init();// 清空脏数据
		int n, m;
		cin >> n >> m; // 读取图的点数和边的数量
		build(n); // 初始化
		for (int i = 0; i < m; ++i) {
			int u, v, w;
			cin >> u >> v >> w; // 读取边的信息
			addEdge(u, v, w); // 添加边
			if (w >= 0) {
				addEdge(v, u, w); // 若权值非负，添加另一条反向边
			}
		}
		// 执行算法并输出结果
		cout << (spfa(n) ? "YES" : "NO") << endl;
		print(n);
	}
	return 0;
}
