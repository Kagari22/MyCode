#include <bits/stdc++.h>

//树状数组模板题1 单点增加 + 范围查询
//https://www.luogu.com.cn/problem/P3374
using namespace std;

const int MAXN = 500001;

vector<int> tree(MAXN, 0);

int n, m;

int lowbit(int i) {
	return i & -i;
}

void add(int i, int v) {
	while (i <= MAXN) {
		tree[i] += v;
		i += lowbit(i);
	}
}

int sum(int i) {
	int ans = 0;
	while (i > 0) {
		ans += tree[i];
		i -= lowbit(i);
	}
	return ans;
}

int range(int l, int r) {
	return sum(r) - sum(l - 1);
}

int main() {
	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		int v;
		cin >> v;
		add(i, v);
	}
	
	for (int i = 1, op, b, c; i <= m; i++) {
		cin >> op >> b >> c;
		if (op == 1) {
			add(b, c);
		} else {
			cout << range(b, c) << '\n';
		}
	}

	return 0;
}

















