#include <bits/stdc++.h>

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_F
// 求出一个点到圆的切线的切点
// from: cpp.json
#define INF 8e18    
#define int long long
#define LD long double
using namespace std;

void solve() {
    LD px, py, cx, cy, r;
    cin >> px >> py >> cx >> cy >> r;

    LD dx = px - cx;
    LD dy = py - cy;
    LD d2 = dx * dx + dy * dy;
    LD d = sqrtl(d2);

    LD l = (r * r) / d2;
    LD h = r * sqrtl(max((LD) 0, d2 - r * r)) / d2;

    LD pdx = -dy, pdy = dx;
    LD vlx = l * dx, vly = l * dy;
    LD vhx = h * pdx, vhy = h * pdy;

    pair<LD, LD> T1 = {cx + vlx + vhx, cy + vly + vhy};
    pair<LD, LD> T2 = {cx + vlx - vhx, cy + vly - vhy};
    
    if (T2.first < T1.first - 1e-12L || 
        (fabsl(T2.first - T1.first) < 1e-12L && T2.second < T1.second - 1e-12L)) {
            swap(T1, T2);
    }
    
    cout << fixed << setprecision(20) << T1.first << ' ' << T1.second << ' ' << T2.first << ' ' << T2.second << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}