#include <bits/stdc++.h>

// https://www.luogu.com.cn/problem/P4525
// 自适应辛普森法求积分
// from: cpp.json
#define INF 8e18
#define LD long double
#define int long long
using namespace std;

LD a, b, c, d, L, R;
const LD eps = 1e-10;

LD f(LD x) {
    return (c * x + d) / (a * x + b);
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
    cin >> a >> b >> c >> d >> L >> R;

    cout << fixed << setprecision(6) << asr(L, R, simpson(L, R)) << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}