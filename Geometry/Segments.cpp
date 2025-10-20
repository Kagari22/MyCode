#include <iostream>
#include <cmath>

// http://poj.org/problem?id=3304
// 给定二维平面中的 n 条线段，判断是否存在一条直线，使得将所有线段投影到这条直线上后，所有投影出的线段至少有一个公共点。
// from: cpp.json
#define INF 8e18
#define int long long
using namespace std;

#define LD long double

struct Point {
    LD x, y;
};

LD cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

const int N = 210;
Point a[N], b[N], p[N];
int n;

const LD eps = 1e-8;

bool check() {
    for (int i = 0; i < 2 * n; i++) {
        for (int j = i + 1; j < 2 * n; j++) {
            LD dx = p[j].x - p[i].x;
            LD dy = p[j].y - p[i].y;
            LD len = sqrt(dy * dy + dx * dx);
            if (len < 1e-12) continue;
            LD ux = dy / len;
            LD uy = -dx / len;
            LD L = -1e300, R = +1e300;
            for (int k = 0; k < n; k++) {
                LD p1 = ux * a[k].x + uy * a[k].y;
                LD p2 = ux * b[k].x + uy * b[k].y;
                LD mn = min(p1, p2), mx = max(p1, p2);
                L = max(L, mn);
                R = min(R, mx);
                if (L > R + 1e-8) break; 
            }
            if (L <= R + 1e-8) {
                return true;
            }
        }
    }
    return false;
}

void solve() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y >> b[i].x >> b[i].y;
    }

    for (int i = 0; i < 2 * n; i++) {
        if (i < n) {
            p[i] = a[i];
        } else {
            p[i] = b[i];
        }
    }

    bool ans = check();
    cout << (ans ? "Yes!\n" : "No!\n");
}

signed main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}