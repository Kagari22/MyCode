#include <bits/stdc++.h>

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/6/CGL_6_A
// 给定 n 条和 X 轴和 Y 轴平行的直线, 求它们之间的交点个数
// from: cpp.json
#define INF 8e18
#define int long long
using namespace std;

template <typename T>
struct Fenwick {
    int n;
    std::vector<T> a;
    
    Fenwick(int n_ = 0) {
        init(n_);
    }
    
    void init(int n_) {
        n = n_;
        a.assign(n + 1, T{});
    }
    
    void add(int x, const T &v) {
        for (int i = x; i <= n; i += i & -i) {
            a[i] += v;
        }
    }
    
    T sum(int x) {
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + a[i];
        }
        return ans;
    }
    
    T rangeSum(int l, int r) {
        if (l > r) return T{};
        return sum(r) - sum(l - 1);
    }
    
    // 前缀和不超过给定值的最小位置的查询
    int select(const T &k) {
        int x = 0;
        T cur{};
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && cur + a[x + i] <= k) {
                x += i;
                cur = cur + a[x];
            }
        }
        return x;
    }
};

struct Event {
    int x, type, y1, y2;  
};

void solve() {
    int n;
    cin >> n;

    vector<tuple<int, int, int, int>> seg(n);
    vector<int> ys;

    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) {
            swap(x1, x2);
        }
        if (y1 > y2) {
            swap(y1, y2);
        }
        seg[i] = {x1, y1, x2, y2};
        ys.push_back(y1);
        ys.push_back(y2);
    }

    ranges::sort(ys);
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    auto getY = [&](int y) -> int {
        return lower_bound(ys.begin(), ys.end(), y) - ys.begin() + 1;
    };

    int m = ys.size();

    vector<Event> e;
    for (auto [x1, y1, x2, y2] : seg) {
        if (y1 == y2) {
            int Y = getY(y1);
            e.push_back({x1, 0, Y, 0});
            e.push_back({x2 + 1, 1, Y, 0});
        } else {
            int Y1 = getY(y1);
            int Y2 = getY(y2);
            e.push_back({x1, 2, Y1, Y2});
        }
    }

    sort(e.begin(), e.end(), [&](auto &a, auto &b) {
        if (a.x != b.x) {
            return a.x < b.x;
        }
        return a.type < b.type;
    });

    Fenwick<int> bit(m + 1);
    int ans = 0;
    for (auto &E : e) {
        if (E.type == 0) {
            bit.add(E.y1, 1);
        } else if (E.type == 1) {
            bit.add(E.y1, -1);
        } else {
            ans += bit.rangeSum(E.y1, E.y2);
        }
    } 

    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}