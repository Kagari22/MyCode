#include <bits/stdc++.h>

// 多测逆序对板题
// https://codeforces.com/contest/1915/problem/F
// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

const int MAXN = 2e5 + 5;
int m;
vector<int> tree(MAXN), Sort(MAXN);

int lowbit(int i) {
    return i & -i;
}

void add(int i, int v) {
    while (i <= m) {
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

int Rank(int v) {
    int l = 1, r = m;
    int ans = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (Sort[mid] >= v) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;

    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }

    sort(a.begin(), a.end());

    vector<int> arr(n + 1);
    fill(Sort.begin(), Sort.end(), 0LL);
    fill(tree.begin(), tree.end(), 0LL);

    for (int i = 1; i <= n; i++) {
        arr[i] = a[i - 1].second;
        Sort[i] = arr[i];
    }

    sort(Sort.begin() + 1, Sort.begin() + n + 1);
    m = 1;

    for (int i = 2; i <= n; i++) {
        if (Sort[m] != Sort[i]) {
            Sort[++m] = Sort[i];
        }
    }

    for (int i = 1; i <= n; i++) {
        arr[i] = Rank(arr[i]);
    }

    int ans = 0;
    for (int i = n; i >= 1; i--) {
        ans += sum(arr[i] - 1);
        add(arr[i], 1); 
    }

    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        solve();
    }

    return 0;
}