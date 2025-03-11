#include <bits/stdc++.h>

// https://ac.nowcoder.com/acm/contest/95480/J
// from: cpp.json
#define INF 1e18
#define int long long
using namespace std;

template<class T>
std::istream& operator>>(std::istream& is, std::vector<T>& v) {
    for(auto &x : v) {
        is >> x;
    }
    return is;
}
 
class FHQTreap {
public:
    FHQTreap() {}
    FHQTreap(int n) {
        init(n);
    }
 
    void add(int num, int c) {
        split(0, 0, head, num);
        key[++cnt] = num;
        size[cnt] = 1;
        priority[cnt] = c;
        head = merge(merge(rs[0], cnt), ls[0]);
    }
 
    void remove(int num) {
        split(0, 0, head, num);
        int lm = rs[0];
        int r = ls[0];
        split(0, 0, lm, num - 1);
        int l = rs[0];
        int m = ls[0];
        head = merge(merge(l, merge(ls[m], rs[m])), r);
    }
 
    int rank(int num) {
        split(0, 0, head, num - 1);
        int ans = size[rs[0]] + 1;
        head = merge(rs[0], ls[0]);
        return ans;
    }
 
    int index(int x) {
        return index(head, x);
    }
 
    int pre(int num) {
        return pre(head, num);
    }
 
    int post(int num) {
        return post(head, num);
    }
 
    int find(int num) {
        int cur = head;
        int ret = 1e18;
        while(cur) {
            if(key[cur] > num) {
                ret = std::min(ret, priority[cur]);
                cur = ls[cur];
            } else if(key[cur] < num) {
                cur = rs[cur];
            } else {
                return std::min(priority[cur], ret);
            }
        }
        return ret;
    }
private:
    void init(int n) {
        head = cnt = 0;
        ls.resize(n + 1, 0);
        rs.resize(n + 1, 0);
        size.resize(n + 1, 0);
        key.resize(n + 1, 0);
        priority.resize(n + 1, 0);
    }
 
    void up(int i) {
        size[i] = size[ls[i]] + size[rs[i]] + 1;
    }
 
    void split(int l, int r, int i, int num) {
        if(i == 0) {
            rs[l] = ls[r] = 0;
        } else {
            if(key[i] <= num) {
                rs[l] = i;
                split(i, r, rs[i], num);
            } else {
                ls[r] = i;
                split(l, i, ls[i], num);
            }
            up(i);
        }
    }
 
    int merge(int l, int r) {
        if(l == 0 || r == 0) {
            return l + r;
        } else {
            if(priority[l] <= priority[r]) {
                rs[l] = merge(rs[l], r);
                up(l);
                return l;
            } else {
                ls[r] = merge(l, ls[r]);
                up(r);
                return r;
            }
        }
    }
 
    int index(int i, int x) {
        if(size[ls[i]] >= x) {
            return index(ls[i], x);
        } else if(size[ls[i]] + 1 < x) {
            return index(rs[i], x - size[ls[i]] - 1);
        } else {
            return key[i];
        }
    }
 
    int pre(int i, int num) {
        if(i == 0) {
            return std::numeric_limits<int>::min();
        }
        if(key[i] >= num) {
            return pre(ls[i], num);
        } else {
            return std::max(key[i], pre(rs[i], num));
        }
    }
 
    int post(int i, int num) {
        if(i == 0) {
            return std::numeric_limits<int>::max();
        }
 
        if(key[i] <= num) {
            return post(rs[i], num);
        } else {
            return std::min(key[i], post(ls[i], num));
        }
    }
 
    int head, cnt;
    std::vector<int> ls, rs, size, key;
    std::vector<int> priority;
};

struct Info {
    int v, c, idx;
};

void solve() {
    int n;
    cin >> n;

    vector<int> v(n), c(n), a(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<Info> arr;
    for (int i = 0; i < n; i++) {
        arr.push_back(Info{v[i], c[i], i});
    }

    FHQTreap fhq(n);

    for (int i = 0; i < n; i++) {
        fhq.add(arr[i].v, arr[i].c);
    }

    for (int i = 0; i < n; i++) {
        int ans = fhq.find(a[i]);
        cout << (ans == INF ? -1 : ans) << " \n"[i == n - 1];
        fhq.remove(arr[i].v);
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        solve();
    }

    return 0;
}