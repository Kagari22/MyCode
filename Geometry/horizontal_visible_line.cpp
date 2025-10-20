#include <bits/stdc++.h>

// https://www.luogu.com.cn/problem/P3194
// 维护上凸包
// from: cpp.json
#define INF 8e18
#define int long long
using namespace std;

#define LD long double

struct Line {
    LD A, B;
    int idx;
};

LD intersectX(const Line &l1, const Line &l2) {
    return (l2.B - l1.B) / (l1.A - l2.A);
}

void solve() {
    int n;
    cin >> n;

    vector<Line> ls(n);
    for (int i = 0; i < n; i++) {
        cin >> ls[i].A >> ls[i].B;
        ls[i].idx = i + 1;
    }

    ranges::sort(ls, [&](auto &l1, auto &l2) {
        if (l1.A != l2.A) {
            return l1.A < l2.A;
        }
        return l1.B > l2.B;
    });

    vector<Line> hull;
    vector<LD> xs;
    for (auto &L : ls) {
        if (!hull.empty() && fabsl(L.A - hull.back().A) < 1e-18) {
            continue;
        }
        while (!hull.empty()) {
            LD x = intersectX(hull.back(), L);
            if (x <= xs.back()) {
                hull.pop_back();
                xs.pop_back();
            } else {
                break;
            }
        }
        LD start = hull.empty() ? -INF : intersectX(hull.back(), L);
        hull.push_back(L);
        xs.push_back(start);
    }

    vector<int> ans;
    for (auto &l : hull) {
        ans.push_back(l.idx);
    }
    ranges::sort(ans);

    for (auto id : ans) {
        cout << id << ' ';
    }
    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}