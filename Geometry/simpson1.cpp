#include <bits/stdc++.h>

// https://www.luogu.com.cn/problem/P4526
// from: cpp.json
#define INF 8e18
#define LD long double
#define int long long
using namespace std;

LD a;
const LD eps = 1e-10;

LD f(LD x) {
    return powl(x, (a / x) - x);
}

LD simpson(LD l, LD r) {
    return (r - l) * (f(l) + f(r) + 4 * f((l + r) / 2)) / 6;
}

LD asr(LD l, LD r, LD ans) {
    auto m = (l + r) / 2;
    auto A = simpson(l, m), B = simpson(m, r);
    if (fabsl(A + B - ans) < eps) {
        return ans;
    }
    return asr(l, m, A) + asr(m, r, B);
}

void solve() {
    cin >> a;
    if (a < 0) {
        cout << "orz\n";
        return;
    }
    cout << fixed << setprecision(5) << asr(eps, 40, simpson(eps, 40)) << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}