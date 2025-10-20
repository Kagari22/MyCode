#include <bits/stdc++.h>

// https://ac.nowcoder.com/acm/contest/27249/C
// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

const double EPS = 1e-9;

struct Point {
    double x, y;

    Point() {}
    Point(double x, double y): x(x), y(y) {}

    Point operator - (const Point &b) const {
        return Point(x - b.x, y - b.y);
    }

    Point operator + (const Point &b) const {
        return Point(x + b.x, y + b.y);
    }

    Point operator * (double t) const {
        return Point(x * t, y * t);
    }

    double dot(const Point &p) const {
        return x * p.x + y * p.y;
    }
};

double cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

Point Get_Insec(Point a, Point b, Point c, Point d) {
    Point ab = b - a;
    Point ac = c - a;
    Point cd = d - c;
    double t = cross(ac, cd) / cross(ab, cd);
    return a + ab * t;
}

double getT(Point s, Point t, Point p) {
    return (abs(s.x - t.x) > EPS) ? (p.x - s.x) / (t.x - s.x) : (p.y - s.y) / (t.y - s.y);
}

void solve() {
    int n, m;
    cin >> n >> m;

    Point s, t;
    cin >> s.x >> s.y >> t.x >> t.y;

    vector<Point> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
    }

    struct Event {
        double t;
        int a, b;

        bool operator<(const Event& other) {
            return t < other.t;
        }
    };

    vector<Event> events;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            Point pi = p[i];
            Point pj = p[j];

            Point insec = Get_Insec(pi, pj, s, t);
            double temp = getT(s, t, insec);
            if (temp > EPS && temp < 1 - EPS) {
                events.push_back({temp, i, j});
            }
        }
    }

    sort(events.begin(), events.end());

    vector<vector<Point>> swaps(n);
    for (auto& e : events) {
        Point insec = s + (t - s) * e.t;
        swaps[e.a].push_back(insec);
        swaps[e.b].push_back(insec);
    }

    while (m--) {
        int h, k;
        cin >> h >> k;
        h--;

        if (k > (int) swaps[h].size()) {
            cout << -1 << '\n';
        } else {
            Point P = swaps[h][k - 1];
            cout << fixed << setprecision(1000) << P.x << ' ' << P.y << '\n';
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}