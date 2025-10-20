#include <bits/stdc++.h>

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_G
// 求两圆的公共切线 (输出圆 C1 上切点的坐标)
// from: cpp.json
#define INF 8e18
#define int long long
#define LD long double
using namespace std;

const LD EPS = 1e-12;

void solve() {
    LD x1, y1, r1, x2, y2, r2;
    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

    LD dx = x2 - x1;
    LD dy = y2 - y1;
    LD D = hypotl(dx, dy);

    vector<pair<LD, LD>> points;
    if (D > EPS) {
        LD base = atan2l(dy, dx);
        LD delta = r1 - r2;
        if (fabs(delta) <= D) {
            LD theta = acosl(delta / D);
            for (int s : {1, -1}) {
                LD ang = base + s * theta;
                LD px = x1 + r1 * cosl(ang);
                LD py = y1 + r1 * sinl(ang);
                points.emplace_back(px, py);
            }
        }
        LD dt = r1 + r2;
        if (dt <= D) {
            LD theta = acosl(dt / D);   
            for (int s : {1, -1}) {
                LD ang = base + s * theta;
                LD px = x1 + r1 * cosl(ang);
                LD py = y1 + r1 * sinl(ang);
                points.emplace_back(px, py);
            }
        }
    }

    sort(points.begin(), points.end(), [&](auto &a, auto &b) {
        if (fabsl(a.first - b.first) > 1e-8L) {
            return a.first < b.first;
        }
        return a.second < b.second;
    });

    vector<pair<LD, LD>> uniq;
    for (auto &p : points) {
        if (uniq.empty() || fabsl(p.first - uniq.back().first) > 1e-8L || fabsl(p.second - uniq.back().second) > 1e-8L) {
            uniq.push_back(p);
        }
    }

    cout << fixed << setprecision(10);
    for (auto &p : uniq) {
        cout << p.first << ' ' << p.second << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}