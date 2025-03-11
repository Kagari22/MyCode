#include <bits/stdc++.h>

// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

const int N = 1e6 + 1;
const int MOD = 998244353;

// mx[i]: i 的最大幂次是多少
// cnt[i][p]: i 的 p 次幂个数
int mx[N], cnt[N][20];

// minp[i]: i 的最小质因子
vector<int> minp, primes;

void sieve(int n) {
    minp.assign(n + 1, 0);
    primes.clear();

    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            primes.push_back(i);
        }

        for (int p : primes) {
            if (i * p > n) {
                break;
            }
            minp[i * p] = p;
            if (p == minp[i]) {
                break;
            }
        }
    }
}

void solve() {
    int n;
    cin >> n;
    
    int v[n];
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    // 存储 v 中所有的质因子
    vector<int> stk;

    // 对每个 v[i] 分解质因子 并计算 v[i] 的每个质因子的最大幂次及其出现次数
    for (int i = 0; i < n; i++) {
        while (v[i] > 1) {
            int p = minp[v[i]];
            int t = 0;
            while (minp[v[i]] == p) {
                v[i] /= p;
                t++;
            }
            // 有新的质因子 塞进去
            if (mx[p] == 0) {
                stk.push_back(p);
            }
            // 计算最大幂次
            mx[p] = max(mx[p], t);
            // 增加出现次数
            // p 的 t 次幂
            cnt[p][t]++;
        }
    }

    vector<int> a(n, 1);

    for (int p : stk) {
        int j = 0;
        // 计算质因子 p 所有出现次数
        for (int i = mx[p]; i; i--) {
            j += cnt[p][i];
        }
        // 累乘计算 p 的 i 次幂
        int pw = 1;
        for (int i = 1; i <= mx[p]; i++) {
            // 累乘
            pw = (pw * p) % MOD;
            // 还有数能乘
            while (cnt[p][i]) {
                cnt[p][i]--;
                // 从 j 到 0 依次从小到大乘数
                j--;
                a[j] = (a[j] * pw) % MOD;
            }
        }
        // 乘完所有数后清 0
        mx[p] = 0;
    }

    int ans = 0;

    for (int i = 0; i < n; i++) {
        ans = (ans + a[i]) % MOD;
    }

    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve(N);

    int t;
    cin >> t;

    while(t--){
        solve();
    }

    return 0;
}