#include <bits/stdc++.h>

// from: cpp.json
#define INF 1e18
#define int long long
using namespace std;

long long MOD = -114514;
const int MAXN = 2e5 + 5;
int base = 131;
long long poww[MAXN];
long long hashh[MAXN];

bool isPrime(long long n) {
    if (n <= 1) return false;
    for (long long i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

void Generate_MOD() {   
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<long long> dist(1e9 + 7, 1e9 + 1145);
    long long prime = dist(rng);
    while (!isPrime(prime)) {
        prime = dist(rng);
    }
    MOD = prime;
    if (MOD < 0) {
        cout << "MOD < 0 BUG!\n";
    }
}

void build(string s, int n) {
    Generate_MOD();
    poww[0] = 1;
    for (int i = 1; i < n; i++) {
        poww[i] = (poww[i - 1] * base) % MOD;
    }
    // 从 1 开始计算 1 到 i 的字符串哈希值
    hashh[0] = s[0] - 'a' + 1;
    for (int i = 1; i < n; i++) {
        hashh[i] = (hashh[i - 1] * base + s[i] - 'a' + 1) % MOD;
    }
}

// l ~ r 的哈希值
int Hash(int l, int r) {
    int ans = hashh[r];
    if(l > 0){
        ans = (ans - (hashh[l - 1] * poww[r - l + 1]) % MOD + MOD) % MOD;
    }
    return ans;
}

void solve() {
    string s = "hello";

    int n = s.size();
    build(s, n);

    int l = 1, r = 3;
    cout << "Hash of substring [" << l << ", " << r << "] : " << Hash(l, r) << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
