//https://www.luogu.com.cn/problem/P3385

/*  ����һ��n���������ͼ��
�����ͼ���Ƿ���ڴӶ���1�����ܵ���ĸ�����
�����Ķ����� : ������Ȩ֮��Ϊ�����Ļ�·��*/

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
// SPFA��Ҫ
#define MAXQ 4000001

// ��ʽǰ���ǽ�ͼ��Ҫ
vector<int> head(MAXN, 0);

vector<int> nextArray(MAXM, 0); // Changed from "next" to "nextArray"

vector<int> to(MAXM, 0);

vector<int> weight(MAXM, 0);

int cnt;

// Դ�������ÿ���ڵ�ľ����
vector<int> dist(MAXN, INT_MAX); // Changed from "distance" to "dist"

// �ڵ㱻�ɳڵĴ���
vector<int> updataCnt(MAXN, 0);

// ��Щ�ڵ㱻�ɳ��˷������
vector<int> q(MAXQ, 0); // Changed from "queue" to "q"

int l, r;

// �ڵ��Ƿ��Ѿ��ڶ�����
vector<bool> enter(MAXN, false);

void print(int n) {
	for (int i = 1; i <= n; i++) {
		printf("��Դ�㵽 ����%d ����̾���Ϊ:", i);
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
		//��ei���������б�
		for (int ei = head[u], v, w; ei > 0; ei = nextArray[ei]) {
			v = to[ei];
			w = weight[ei];
			if (dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				if (!enter[v]) {
					//���ָ���
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
	cin >> T; // ��ȡ�������ݵ�����
	while (T--) {
		Init();// ���������
		int n, m;
		cin >> n >> m; // ��ȡͼ�ĵ����ͱߵ�����
		build(n); // ��ʼ��
		for (int i = 0; i < m; ++i) {
			int u, v, w;
			cin >> u >> v >> w; // ��ȡ�ߵ���Ϣ
			addEdge(u, v, w); // ��ӱ�
			if (w >= 0) {
				addEdge(v, u, w); // ��Ȩֵ�Ǹ��������һ�������
			}
		}
		// ִ���㷨��������
		cout << (spfa(n) ? "YES" : "NO") << endl;
		print(n);
	}
	return 0;
}
