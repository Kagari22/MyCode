#include <bits/stdc++.h>

//树状数组模版题2 范围增加 + 单点查询
//https://www.luogu.com.cn/problem/P3368
//在 l - r 上 增加 k,等于在差分数组nums中 nums[l] + k , nums[r + 1] - k

using namespace std;

#define MAXN 500002

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

/*int range(int l, int r) {
	return sum(r) - sum(l - 1);
}*/

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		int v;
		cin >> v;
		add(i, v);
		add(i + 1, -v);
	}

	for (int i = 1, op; i <= m; i++) {
		cin >> op;
		if (op == 1) {
			int l, r, v;
			cin >> l >> r >> v;
			// 将区间 [l, r] 每个数加上 v 
			add(l, v);
			add(r + 1, -v);
		}
		else {
			int index;
			cin >> index;
			// 输出第 index 个数的值
			cout << sum(index) << '\n';
		}
	}

	return 0;
}

















